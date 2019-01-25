package com.hospital.reception.adapters;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import com.hospital.reception.application_logic.ReceptionService;
import com.hospital.reception.domain.HospitalStay;

@RestController
public class ReceptionRestController {
	@Autowired
	private ReceptionService service;
	
	
	@RequestMapping(value="/reception/hospital_stays", method=RequestMethod.GET)
	public Iterable<HospitalStay> findAll() {
		return service.findAll();
	}
	
	@RequestMapping(value="/reception/get_patient_booking/{patientId}", method=RequestMethod.GET)
	public Optional<HospitalStay> findPatientBooking(@PathVariable("patientId") String patientId){
		return service.findPatientBooking(patientId);
	}
	
	
	
}
