package com.hospital.reception.domain;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;


@Entity
public class HospitalStay {

	@Id @GeneratedValue(strategy=GenerationType.IDENTITY)
	public long Id;
	public String patientId;
	public String wardId;
	public String bedId;
	@Temporal(TemporalType.DATE)
	public Date dateOfStay;
	public Status status;
	
	public HospitalStay() {}
	
	public HospitalStay(String patientId, String wardId, String bedId, Date dateOfStay, Status status) {
		this.patientId = patientId;
		this.wardId = wardId;
		this.bedId = bedId;
		this.dateOfStay = dateOfStay;
		this.status = status;
	}
	
	@Override
	public String toString() {
		return String.format("Id: %d\npatientId: %s\nwardId: %s\nbedId: %s\nDate of stay: %s\nStatus: %s\n\n", Id,patientId,wardId,bedId,dateOfStay,status);
	}
	
	
}
