#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 1

int
main(int argc, char *argv[])
{
	int i, myrank, nprocs;
	int *send_buffer;
	int *recv_buffer;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	send_buffer = new int[N];

	for (i = 0; i < N; i++)
		send_buffer[i] = myrank;

	// 在每个进程上, recv_buffer的大小为所有进程的send_buffer大小之和.
	recv_buffer = new int[nprocs * N];

	MPI_Allgather(send_buffer, N, MPI_INT,
		recv_buffer, N, MPI_INT, MPI_COMM_WORLD);

	for (i = 0; i < nprocs * N; i++)
		printf("%d buffer %d = %d\n", myrank, i, recv_buffer[i]);

	fprintf(stderr, "\n");
	delete[]recv_buffer;
	delete[]send_buffer;
	MPI_Finalize();
	return 0;
}