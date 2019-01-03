package com.hospital.patient_management.domain;

import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

@Entity
public class Patient {
	
	@Id
	public String ssn;	 
	
	public String firstName;
	public String lastName;
	
	@Temporal(TemporalType.DATE)
	public Date dateOfBirth;
	
	public Patient() {} // default constructor for hibernate
	
	public Patient(String ssn, String firstName, String lastName, Date dateOfBirth) {
		this.ssn = ssn;
		this.firstName = firstName;
		this.lastName = lastName;
		this.dateOfBirth = dateOfBirth;
	}
	
	@Override
	public String toString() {
		return String.format("%s %s geboren op %s en ssn = %s", firstName, lastName, dateOfBirth.toString(), ssn);
	}
	
	
}
