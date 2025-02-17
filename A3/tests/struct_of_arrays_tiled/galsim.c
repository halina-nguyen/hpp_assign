#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include "../../graphics/graphics.h"

#define WINDOW_WIDTH 800

typedef struct {
    double* x;
    double* y;
    double* m;
    double* u;
    double* v;
    double* b;
} particleset_t;
 
static inline void update(particleset_t *particles_ptr, int N, double delta_t) {
    const double G = 100.0 / N;
    const double eps_0 = 1.0e-3;
    const int block_size = 80;
    double *x = particles_ptr->x;
    double *y = particles_ptr->y;
    double *u = particles_ptr->u;
    double *v = particles_ptr->v;
    double *m = particles_ptr->m;
    int blocks_n = (N / block_size) * block_size;
    for (int block_i = 0; block_i < blocks_n; block_i += block_size) {
        int i_end = block_i + block_size;
        for (int block_j = block_i; block_j < blocks_n; block_j += block_size) {
            int j_end = block_j + block_size;
            for (int i = block_i; i < i_end; ++i) {
                double ai_x = 0, ai_y = 0;
                int j_start = (block_j > i)*block_j + (block_j <= i)*(i+1);
#pragma GCC ivdep
                for (int j = j_start; j < j_end; ++j) {
                    double r_ij, dx, dy, f_i, f_j, k;
                    dx = x[i] - x[j];
                    dy = y[i] - y[j];
                    r_ij = sqrtf(dx*dx + dy*dy) + eps_0;
                    k = -G / (r_ij * r_ij * r_ij);
                    f_i = k * m[j];
                    f_j = k * m[i];
                    ai_x += f_i * dx;
                    ai_y += f_i * dy;
                    u[j] -= delta_t * f_j * dx;
                    v[j] -= delta_t * f_j * dy;
                }
                u[i] += delta_t * ai_x;
                v[i] += delta_t * ai_y;
            }
        }
    }
#pragma GCC ivdep
    for (int i = 0; i < N; ++i) {
        x[i] += delta_t * u[i];
        y[i] += delta_t * v[i];
    }
}

static inline void simulate(particleset_t *particles_ptr, int N, int n_steps, double delta_t) {
    for (int step = 0; step < n_steps; ++step) {
        update(particles_ptr, N, delta_t);
    }
}

void draw_particles(particleset_t *particles_ptr, int N) {
    const float circleColor = 0;
    const float L = 1, W = 1;
    ClearScreen();
    for (int i = 0; i < N; ++i) {
        DrawCircle(particles_ptr->x[i], particles_ptr->y[i], L, W, 0.0025, circleColor);
    }
    Refresh();
    usleep(3000);
}

static inline void simulate_with_graphics(particleset_t *particles_ptr, int N, int n_steps, double delta_t) {
    for (int step = 0; !CheckForQuit() && step < n_steps; ++step) {
        update(particles_ptr, N, delta_t);
        draw_particles(particles_ptr, N);
    }
}

particleset_t *read_input(char *file_name, int *N_ptr) {
    FILE *stream = fopen(file_name, "rb");
    if (!stream) {
        return NULL;
    }
    int N = *N_ptr;
    size_t particle_size = 6*sizeof(double);
    double *buf = (double *)malloc(N*particle_size);
    particleset_t *particles_ptr = (particleset_t *)malloc(sizeof(particleset_t));
    int read_count = fread(buf, particle_size, N, stream);
    if (read_count != N) {
        printf("Warning: number of particles in file is %d\n", read_count);
        *N_ptr = read_count;
        N = *N_ptr;
        buf = realloc(buf, N*particle_size);
    }
    fclose(stream);
    void *mem = malloc(N*particle_size);
    particles_ptr->x = mem;
    particles_ptr->y = mem + N*sizeof(double);
    particles_ptr->m = mem + 2*N*sizeof(double);
    particles_ptr->u = mem + 3*N*sizeof(double);
    particles_ptr->v = mem + 4*N*sizeof(double);
    particles_ptr->b = mem + 5*N*sizeof(double);
    for (int i = 0; i < N; ++i) {
        particles_ptr->x[i] = buf[i*6];
        particles_ptr->y[i] = buf[i*6 + 1];
        particles_ptr->m[i] = buf[i*6 + 2];
        particles_ptr->u[i] = buf[i*6 + 3];
        particles_ptr->v[i] = buf[i*6 + 4];
        particles_ptr->b[i] = buf[i*6 + 5];
    }
    free(buf);
    return particles_ptr;
}

int write_output(char *file_name, particleset_t *particles_ptr, int N) {
    FILE *stream = fopen(file_name, "wb");
    if (!stream) {
        return -1;
    }
    size_t particle_size = 6*sizeof(double);
    double *buf = (double *)malloc(N*particle_size);
    for (int i = 0; i < N; ++i) {
        buf[i*6] = particles_ptr->x[i];
        buf[i*6 + 1] = particles_ptr->y[i];
        buf[i*6 + 2] = particles_ptr->m[i];
        buf[i*6 + 3] = particles_ptr->u[i];
        buf[i*6 + 4] = particles_ptr->v[i];
        buf[i*6 + 5] = particles_ptr->b[i];
    }
    long write_count = fwrite(buf, particle_size, N, stream);
    if (write_count != N) {
        fclose(stream);
        return -1;
    }
    free(buf);
    fclose(stream);
    return write_count;
}

/* From Lab 6 */
static double get_wall_seconds() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double seconds = tv.tv_sec + (double)tv.tv_usec / 1000000;
    return seconds;
}

int main(int argc, char** argv) {
    int N, n_steps;
    char *file_name, graphics;
    double delta_t;

    if (argc != 6) {
        printf("usage: galsim N filename nsteps delta_t graphics\n");
        return 1;
    }

    N = atoi(argv[1]);
    file_name = argv[2];
    n_steps = atoi(argv[3]);
    delta_t = atof(argv[4]);
    graphics = atoi(argv[5]);

    particleset_t *particles_ptr = read_input(file_name, &N);

    if (!particles_ptr) {
        printf("file not found: %s\n", file_name);
        return 1;
    }

    if (graphics) {
        printf("Hit q to quit.\n");
        InitializeGraphics(argv[0], WINDOW_WIDTH, WINDOW_WIDTH);
        SetCAxes(0,1);
        simulate_with_graphics(particles_ptr, N, n_steps, delta_t);
        FlushDisplay();
        CloseDisplay();
    }
    else
    {
        double time1 = get_wall_seconds();
        simulate(particles_ptr, N, n_steps, delta_t);
        printf("%.3f wall seconds (%s, %7d steps)\n", get_wall_seconds()-time1, file_name, n_steps);
    }

    if (write_output("result.gal", particles_ptr, N) < 0) {
        printf("Failed to write output to result.gal\n");
        free(particles_ptr->x);
        free(particles_ptr);
        return 1;
    }

    free(particles_ptr->x);
    free(particles_ptr);
    return 0;
}
