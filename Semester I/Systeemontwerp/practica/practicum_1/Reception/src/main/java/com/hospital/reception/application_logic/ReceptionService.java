package com.hospital.reception.application_logic;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import com.hospital.reception.domain.HospitalStay;
import com.hospital.reception.persistence.HospitalStayRepository;

@Component
public class ReceptionService {

	@Autowired
	private HospitalStayRepository repository;
	
	
	
	
	public Iterable<HospitalStay> findAll(){
		return repository.findAll();
	}
	
	public Optional<HospitalStay> findPatientBooking(String patientId){
		return repository.findPatientBooking(patientId);
	}
}
