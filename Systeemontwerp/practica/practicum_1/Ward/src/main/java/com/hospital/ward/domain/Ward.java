package com.hospital.ward.domain;

import java.util.ArrayList;
import java.util.List;

import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.OneToMany;

@Entity
public class Ward {
	@Id @GeneratedValue(strategy=GenerationType.IDENTITY)
	public Long id;
	
	@OneToMany(cascade = CascadeType.ALL, mappedBy="ward", fetch = FetchType.EAGER)
	private List<Bed> beds;
	
	public Ward() {
		beds = new ArrayList<Bed>();
	}
	
	public Ward(ArrayList<Bed> beds) {
		this.beds = beds;
	}
	
	public void addBed(String patientId) {
		beds.add(new Bed(this, patientId));
	}
}
