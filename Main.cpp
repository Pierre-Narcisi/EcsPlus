//
// Created by seb on 07/01/19.
//

#include <iostream>
#include <ecs/Ecs.hpp>
#include <ecs/Time.hpp>
#include <thread>
#include <ecs/ThreadPool.hpp>

int main() {
	std::cout << "Hello, World!" << std::endl;
	ID id;

	long time;
	auto &ecs = ecs::Ecs::get();

	for (int i = 0; i < 1000; i++) {
		id = ecs::entity::Entity::getId();
		ecs.addComponent<int>(id, i);
	}


	auto ids = ecs.filter<int>();
	auto ints = ecs.getComponentMap<int>();
	time = ecs::Time::get(TimeUnit::MilliSeconds);

	for (auto id : ids) {
		for (auto od : ids) {
			std::this_thread::sleep_for(std::chrono::nanoseconds(100));
		}
	}

	std::cout << ecs::Time::get(TimeUnit::MilliSeconds) - time << std::endl;

	time = ecs::Time::get(TimeUnit::MilliSeconds);

	ThreadPool<std::pair<ID,ID>> pool([&ints](std::pair<ID, ID> check) {
		std::this_thread::sleep_for(std::chrono::nanoseconds(100));
	}, 4);

	for (auto id : ids) {
		pool.lockWork();
		for (auto od : ids) {
			pool.addTask(std::pair<ID, ID>(id, od));
		}
		pool.unlockWork();
		while (!pool.isDone());
	}
	std::cout << ecs::Time::get(TimeUnit::MilliSeconds) - time << std::endl;

	return 0;
}
