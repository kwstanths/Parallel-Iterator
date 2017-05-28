#ifndef __MYPARALLELFOR_HPP__
#define __MYPARALLELFOR_HPP__

#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <assert.h>
#include <math.h>

#include "myWorkset.hpp"
#include "myThreadPool.hpp"
#include "myParallelIterator.hpp"

namespace mns{

namespace parallel_for{

	/*
	      -All processes are inserted into a thread pool and are executed by random threads in a FIFO ordering
	*/
	void for_each(std::vector<std::function<void()> >& funcs, int num_threads);

	/*
		-The processes are seperated into portions of size chunk_size. Each portion is given to each thread in a round robin manner
		-For chunk_size=1, processes are executed in a classic round robin
		-Work is seperated statically, potentially leading to load imbalance. When all the portions that belong to a thread finish execution,
			the thread awaits the other threads
		For chunk_size=0, chunk_size is calculated based on the amount of processes and num_threads, in order for each thread to execute exactly one portion
	*/
	void for_each(std::vector<std::function<void()> >& funcs, int num_threads, int chunk_size);

	/*
		-num_threads workers are created. Each worker gets the next ws item and executes func(item)
		-Execution finishes when ws is empty, and all threads have finished their execution
	*/
	template <typename T> void for_each(mns::data_structs::Workset<T> * ws, std::function<void(T)> func, int num_threads){
		mns::ParallelIterator::ParallelIterator<T> pool(ws, func, num_threads);

		pool.wait_finish();

		return;
	}
}

}

#endif
