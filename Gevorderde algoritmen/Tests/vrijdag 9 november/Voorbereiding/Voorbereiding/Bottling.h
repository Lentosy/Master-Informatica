#pragma once


#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include <algorithm>

class Bottle;

class Bottling {
public:
	Bottling() = default;
	Bottling(const std::vector<Bottle>& bottles);
	int getOptimalBottles(int volumeToReach);
	friend std::ostream& operator<<(std::ostream& os, const Bottling& bottling);

private:
	std::vector<Bottle> availableBottles;
	void printMatrix(const std::vector<std::vector<int>>& m) const;
};


class Bottle {
public:
	Bottle(unsigned int vol) : Bottle(vol, std::numeric_limits<unsigned int>::max()) {}
	Bottle(unsigned int vol, unsigned int amount) : volume{ vol }, amountAvailable{ amount } {}
	unsigned int volume; // volume in cl that a bottle can hold
	unsigned int amountAvailable; // how many of  these bottles are available
	friend std::ostream& operator<<(std::ostream& os, const Bottle& bottle);

};

Bottling::Bottling(const std::vector<Bottle>& bottles) : availableBottles{ std::move(bottles) } {}

int Bottling::getOptimalBottles(int volumeToReach) {
//???
}



std::ostream& operator<<(std::ostream& os, const Bottling& bottling) {
	os << "Welcome to the bottling machine. We currently have the following bottles in storage:\n";
	os << std::setw(10) << "volume" << std::setw(16) << "amount";
	os << "\n";
	for (size_t i = 0; i < bottling.availableBottles.size(); i++) {
		os << bottling.availableBottles[i];
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const Bottle& bottle) {
	os << std::setw(7) << bottle.volume << " cl " << std::setw(15) << bottle.amountAvailable << "\n";
	return os;
}