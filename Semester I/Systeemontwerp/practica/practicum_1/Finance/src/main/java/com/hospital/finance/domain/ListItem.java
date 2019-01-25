package com.hospital.finance.domain;

public class ListItem {
	
	public String name;
	public double cost;
	
	public ListItem(String name, double cost) {
		this.name = name;
		this.cost = cost;
	}
	
	@Override
	public String toString() {
		return String.format("[%s, %.2f]", name, cost);
	}
}
