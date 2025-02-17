#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>
#include "../../graphics/graphics.h"

#define WINDOW_WIDTH 800

typedef struct {
    double x;
    double y;
    double m;
    double u;
    double v;
    double b;
} particle_t;

static inline void update(particle_t *particles, int N, double delta_t) {
    const double G = 100.0 / N;
    const double eps_0 = 1.0e-3;
    particle_t *p_i, *p_end = particles + N;
    for (p_i = particles; p_i < p_end; p_i++) {
        double ai_x = 0, ai_y = 0;
        for (particle_t *p_j = particles; p_j < p_end; p_j++) {
            double r_ij, dx, dy, f;
            dx = p_i->x - p_j->x;
            dy = p_i->y - p_j->y;
            r_ij = sqrt(dx*dx + dy*dy) + eps_0;
            f = -G * p_j->m / (r_ij * r_ij * r_ij);
            ai_x += f * dx;
            ai_y += f * dy;
        }
        p_i->u += delta_t * ai_x;
        p_i->v += delta_t * ai_y;
    }
    for (p_i = particles; p_i < p_end; p_i++) {
        p_i->x += delta_t * p_i->u;
        p_i->y += delta_t * p_i->v;
    }
}

static inline void simulate(particle_t *particles, int N, int n_steps, double delta_t) {
    for (int step = 0; step < n_steps; ++step) {
        update(particles, N, delta_t);
    }
}

void draw_particles(particle_t *particle, int N) {
    const float circleColor = 0;
    const float L = 1, W = 1;
    ClearScreen();
    for (int i = 0; i < N; ++i) {
        DrawCircle(particle->x, particle->y, L, W, 0.0025, circleColor);
        particle++;
    }
    Refresh();
    usleep(3000);
}

static inline void simulate_with_graphics(particle_t *particles, int N, int n_steps, double delta_t) {
    for (int step = 0; !CheckForQuit() && step < n_steps; ++step) {
        update(particles, N, delta_t);
        draw_particles(particles, N);
    }
}

particle_t *read_input(char *file_name, int *N_ptr) {
    FILE *stream = fopen(file_name, "rb");
    if (!stream) {
        return NULL;
    }
    int N = *N_ptr;
    particle_t *particles = (particle_t *)malloc(N*sizeof(particle_t));
    int read_count = fread(particles, sizeof(particle_t), N, stream);
    if (read_count != N) {
        printf("Warning: number of particles in file is %d\n", read_count);
        *N_ptr = read_count;
        N = *N_ptr;
        particles = realloc(particles, N*sizeof(particle_t));
    }
    fclose(stream);
    return particles;
}

int write_output(char *file_name, particle_t *particles, int N) {
    FILE *stream = fopen(file_name, "wb");
    if (!stream) {
        return -1;
    }
    long N_written = fwrite(particles, sizeof(particle_t), N, stream);
    if (N_written != N) {
        fclose(stream);
        return -1;
    }
    fclose(stream);
    return N_written;
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

    particle_t *particles = read_input(file_name, &N);

    if (!particles) {
        printf("file not found: %s\n", file_name);
        return 1;
    }

    if (graphics) {
        printf("Hit q to quit.\n");
        InitializeGraphics(argv[0], WINDOW_WIDTH, WINDOW_WIDTH);
        SetCAxes(0,1);
        simulate_with_graphics(particles, N, n_steps, delta_t);
        FlushDisplay();
        CloseDisplay();
    }
    else
    {
        double time1 = get_wall_seconds();
        simulate(particles, N, n_steps, delta_t);
        printf("%.3f wall seconds (%s, %7d steps)\n", get_wall_seconds()-time1, file_name, n_steps);
    }

    if (write_output("result.gal", particles, N) < 0) {
        printf("Failed to write output to result.gal\n");
        free(particles);
        return 1;
    }

    free(particles);
    return 0;
}
