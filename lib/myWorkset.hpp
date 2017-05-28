#ifndef __MYWORKSET_HPP__
#define __MYWORKSET_HPP__

#include <iostream>
#include <queue>
#include <functional>
#include <mutex>
#include <sched.h>
#include <thread>

namespace mns{

namespace data_structs{

      template <typename T> struct generic_work_item{
            T item_;
            std::function<void(T)> func_;
            generic_work_item(std::function<void(T)> func, T item){
                  item_ = item;
                  func_ = func;
            }
            void operator()(){
                  func_(item_);
            }
      };

      struct parallel_for_work_item{
            int start_, chunk_, step_;
            std::vector<std::function<void()> >& items_;
            parallel_for_work_item(int start, int chunk, int step, std::vector<std::function<void()> >& items): start_(start), chunk_(chunk), step_(step), items_(items){};

            void run(){
                  for(int i=start_; i<items_.size(); i +=step_){
                        for(int j=i; j<items_.size() && j<i+chunk_ ; j++){
                              items_.at(j)();
                        }
                  }
            }
      };

      template <typename T> class Workset{
      public:
            Workset(){ };

            Workset(std::queue<T> ws){
                  tasks = ws;
            }

            void push(T task){
                  lock.lock();
                  tasks.push(task);
                  lock.unlock();
            }

            T pop(){
                  lock.lock();
                  T temp = tasks.front();
                  tasks.pop();
                  lock.unlock();

                  return temp;
            }

            int size(){
                  lock.lock();
                  int sz = tasks.size();
                  lock.unlock();

                  return sz;
            }

            bool empty(){
                  return size()?false:true;
            }

      private:
            std::queue<T> tasks;
            std::mutex lock;
      };

}

}

#endif
