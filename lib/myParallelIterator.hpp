#ifndef __MYPARALLELITERATOR_HPP__
#define __MYPARALLELITERATOR_HPP__

#include <iostream>
#include <vector>
#include <functional>
#include <queue>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

#include "myWorkset.hpp"

namespace mns{

namespace ParallelIterator {

	template <typename T> class ParallelIterator{

		class Worker{
			ParallelIterator<T> * parallelIterator_;
		public:
			Worker(ParallelIterator<T> * parallelIterator){
				parallelIterator_ = parallelIterator;
			}

			void run(){
				while(1){
					T item;
					{
						std::unique_lock<std::mutex> l(parallelIterator_->lock_);
						parallelIterator_->available_workers_++;
						parallelIterator_->condition_.notify_all();
						parallelIterator_->condition_.wait(l, [&](){return !parallelIterator_->ws_->empty() || (parallelIterator_->available_workers_ == parallelIterator_->num_threads_ && parallelIterator_->ws_->empty());});

						if (parallelIterator_->available_workers_ == parallelIterator_->num_threads_ && parallelIterator_->ws_->empty()) return;

						item = parallelIterator_->ws_->pop();
						parallelIterator_->available_workers_--;
					}

					mns::data_structs::generic_work_item<T> task(parallelIterator_->func_, item);
					task();
				}
			}
		};

		std::function<void(T)> func_;
		mns::data_structs::Workset<T> * ws_;
		int num_threads_;
		std::vector<std::thread> workers_;


		std::mutex lock_;
		std::condition_variable condition_;

		std::atomic<int> available_workers_;

	public:
		ParallelIterator(mns::data_structs::Workset<T> * ws, std::function<void(T)> func, int num_threads){
			available_workers_ = 0;
			func_ = func;
			ws_ = ws;
			num_threads_ = num_threads;
			for (int i = 0; i < num_threads; i++){
				workers_.push_back(std::thread(&Worker::run, new Worker(this)));
			}
		}

		void wait_finish(){
			condition_.notify_all();
			for (std::vector<std::thread>::iterator itr = workers_.begin(); itr != workers_.end(); itr++) itr->join();

			return;
		}
	};
}

}
#endif
