package com.hospital.ward.domain;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;

import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

@Entity
public class Bed {

	@Id @GeneratedValue(strategy=GenerationType.IDENTITY)
	public long id;
	public String patientId;
	
	@ManyToOne(fetch = FetchType.EAGER, optional = false)
	@JoinColumn(name = "ward_id", nullable = false)
	@OnDelete(action = OnDeleteAction.CASCADE)
	private Ward ward;

	public Bed() {}
	
	public Bed(Ward ward, String patientId) {
		this.patientId = patientId;
		this.ward = ward;
	}
	
	public boolean isOccupied() {
		return patientId == null;
	}
}
