#include "myParallelFor.hpp"

namespace mns{

namespace parallel_for{

      void for_each(std::vector<std::function<void()> >& funcs, int num_threads){
            assert(num_threads > 0);
            mns::ThreadPool::ThreadPool threadpool(num_threads);

            for(std::vector<std::function<void()> >::iterator itr = funcs.begin(); itr != funcs.end(); ++itr)
                  threadpool.schedule((*itr));

            threadpool.wait_finish();
      }

      void for_each(std::vector<std::function<void()> >& funcs, int num_threads, int chunk_size){
            assert(num_threads > 0);

            int chunk_size_ = chunk_size;

            if (chunk_size_ == 0){
                  chunk_size_ = ceil(funcs.size() / num_threads);
            }

            std::vector<mns::data_structs::parallel_for_work_item *> thread_items;
            for(int i=0; i<num_threads; i++){
                  thread_items.push_back(new mns::data_structs::parallel_for_work_item(i*chunk_size_, chunk_size_, num_threads*chunk_size_, funcs));
            }

            std::vector<std::thread> threads;
            for(int i=0; i<num_threads; i++){
                  threads.push_back(std::thread(&mns::data_structs::parallel_for_work_item::run, thread_items.at(i)));
                  cpu_set_t cpuset;
                  CPU_ZERO(&cpuset);
                  CPU_SET(i, &cpuset);
                  int rc = pthread_setaffinity_np(threads.at(i).native_handle(), sizeof(cpu_set_t), &cpuset);
                  assert(rc == 0);
            }

            for(int i=0; i<num_threads; i++)
                  threads.at(i).join();
      }

}

}
