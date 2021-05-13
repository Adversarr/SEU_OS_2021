#define _GNU_SOURCE
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sched.h>

#define NDEBUG


struct mm_info
{
    float *A;
    float *B;
    int n, m, k;
    float *out;
};

// do matmul store in out
void *mm(void *info)
{
    struct mm_info *pinfo = (struct mm_info *)info;
    float *A = pinfo->A;
    float *B = pinfo->B;
    int n = pinfo->n,
        m = pinfo->m,
        k = pinfo->k;
    float *C = pinfo->out;

#ifndef NDEBUG
    printf("[Info] I'm going to do matmul...\n");
    printf("\tMat A: address = %p\n", A);
    printf("\tMat B: address = %p\n", B);
    printf("\tMat C: address = %p\n", C);
    printf("\tn, m, k = %d, %d, %d\n", n, m, k);
#endif
    // clear
    for (int i = 0; i < n * k; ++i)
        C[i] = 0.0f;

    for (int i = 0; i < n; ++i)
    {
        for (int k_ = 0; k_ < m; ++k_)
        {
            for (int j = 0; j < k; ++j)
            {
                C[i * k + j] += A[i * m + k_] * B[k_ * k + j];
            }
        }
    }
}

// read from text
float *read_matrix(int *m, int *n, char *fn)
{
    FILE *file = fopen(fn, "r");
    if (file == NULL)
    {
        printf("[Error] I cannot read file %s.\n", fn);
    }
    fscanf(file, "%d", n);
    fscanf(file, "%d", m);
    float *mat = (float *)malloc(sizeof(float) * (*n) * (*m));
    for (int i = 0; i < (*n) * (*m); ++i)
    {
        fscanf(file, "%f", &(mat[i]));
    }

    fclose(file);
    return mat;
}

// write to text
void write_matrix(float *mat, int *m, int *n, char *fn)
{
    FILE *file = fopen(fn, "w");
    fprintf(file, "%d %d\n", *m, *n);
    for (int i = 0; i < *n; ++i)
    {
        for (int j = 0; j < *m; ++j)
        {
            fprintf(file, "%f ", mat[i * (*m) + j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main(int argc, char **argv)
{
    // mm -a mata.txt -b matb.txt -t nthreads
    if (argc != 7)
    {
        printf("[Error] Illegal Param For matmul.");
        return 1;
    }

    int m_A, m_B, n_A, n_B;
    float *A, *B, *C;
    time_t start = time(NULL), end;
#ifndef NDEBUG
    printf("[Info] I wanna read A from %s and B from %s...\n", argv[2], argv[4]);
#endif

    A = read_matrix(&m_A, &n_A, argv[2]);
    B = read_matrix(&m_B, &n_B, argv[4]);
#ifndef NDEBUG
    printf("[Info] I got mat A <at %p> and mat B <at %p>\n", A, B);
#endif
    int nthread = atoi(argv[6]);
    if (m_A != n_B)
    {
        printf("[Error] Illegal shape For matmul, got m1, m2 = [%d, %d]", m_A, n_B);
    }

    int m_C = m_B,
        n_C = n_A;
    C = (float *)malloc(sizeof(float) * n_C * m_C);

    
    

    struct mm_info *t_info = malloc(sizeof(struct mm_info) * nthread);
    int rows_each_thread = n_A / nthread;
    pthread_t *tid = malloc(sizeof(pthread_t) * nthread);

    for (int it = 0; it < nthread; ++it)
    {
        cpu_set_t cpu;
        CPU_ZERO(&cpu);
        int start = rows_each_thread * it,
            end = (it != (nthread - 1)) ? (rows_each_thread * (it + 1)) : n_A;
        CPU_SET(it % 8, &cpu);
        t_info[it].A = A + start * m_A;
        t_info[it].B = B;
        t_info[it].n = end - start;
        t_info[it].m = m_A;
        t_info[it].k = m_B;
        t_info[it].out = C + start * m_C;
#ifndef NDEBUG
        printf("n, m, k = %d, %d, %d\n", t_info[it].n, t_info[it].m, t_info[it].k);
#endif
        pthread_create(tid + it, NULL, mm, t_info + it);
        pthread_setaffinity_np(tid[it], sizeof(cpu_set_t), &cpu);
    }

    for (int it = 0; it < nthread; ++it){
        pthread_join(tid[it], NULL);
    }
    write_matrix(C, &m_C, &n_C, "result.txt");
    
    end = time(NULL);
    printf("Done in %lf s...\n", difftime(end, start));
    free(A);
    A = NULL;
    free(B);
    B = NULL;
    free(C);
    C = NULL;
    free(tid);
    tid = NULL;
    free(t_info);
    t_info = NULL;
    return 0;
}