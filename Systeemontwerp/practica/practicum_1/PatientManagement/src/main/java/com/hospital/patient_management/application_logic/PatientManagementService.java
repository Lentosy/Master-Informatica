package com.hospital.patient_management.application_logic;


import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import com.hospital.patient_management.domain.Patient;
import com.hospital.patient_management.persistence.PatientRepository;

@Component
public class PatientManagementService {
	
	@Autowired
	private PatientRepository repository;
	
	public Iterable<Patient> findAll(){
		return repository.findAll();
	}
	
	public Optional<Patient> findById(String ssn){
		return repository.findById(ssn);
	}
	
	public Iterable<Patient> getPatientsYoungerThan(int age){
		return repository.getPatientsYoungerThan(age);
	}
	
	public Iterable<Patient> getPatientsByFirstName(String name){
		return repository.getPatientsByFirstName(name);
	}
	
	public void addPatient(Patient patient) {
		repository.save(patient);
	}
}
