#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <atomic>
#include <unistd.h>
#include <sched.h>

#include "myParallelFor.hpp"
#include "myWorkset.hpp"

//std::atomic<int> global_variable;
long int global_variable;

typedef struct process{
	long int loop_times_ = 0;
	bool op_;
	process(long int loop_times, bool op){
		loop_times_ = loop_times;
		op_ = op;
	}
	void operator()(){
		std::cout << "Thread: " << sched_getcpu() << ", Operation: " << op_ << std::endl;
		for(long int i=0; i<loop_times_; i++)
			if (op_) global_variable++;
			else global_variable--;
		return;
	}

} process_t;

typedef struct workItem{
	int loop_times_;
	workItem(int loop_times){
		loop_times_ = loop_times;
	}
} workItem_t;

mns::data_structs::Workset<workItem_t *> * tasks;

struct process_1{
 	void operator()(workItem_t * item){
		for(int i=0; i<1000000000; i++);

		int loop_times = --item->loop_times_;
		std::cout << "Times: " << loop_times << std::endl;
		if (item->loop_times_> 0) tasks->push(new workItem_t(loop_times));
		if (item->loop_times_> 0) tasks->push(new workItem_t(loop_times));
	}
};


int main(){
	//Testing random parallel for
	global_variable=0;
	std::vector<std::function<void()> > procs;
	procs.push_back(process_t(1000000,true));
	procs.push_back(process_t(1000000,false));
	procs.push_back(process_t(1000000,true));
	procs.push_back(process_t(1000000,false));
	procs.push_back(process_t(1000000, true));
	procs.push_back(process_t(1000000,false));
	mns::parallel_for::for_each(procs, 2);
	std::cout << global_variable << std::endl;

	//Testing chunked round robin parallel for
	std::cout << "Chunked" << std::endl;
	global_variable = 0;
	mns::parallel_for::for_each(procs, 2, 2);
	std::cout << global_variable << std::endl;

	global_variable = 0;
	mns::parallel_for::for_each(procs, 2, 0);
	std::cout << global_variable << std::endl;

	//Testing parallel iterator
	tasks = new mns::data_structs::Workset<workItem_t *>();
	tasks->push(new workItem_t(2));

	mns::parallel_for::for_each<workItem_t *>(tasks, process_1(), 2);

}
