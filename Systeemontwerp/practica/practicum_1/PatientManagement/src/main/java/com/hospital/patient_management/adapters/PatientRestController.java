package com.hospital.patient_management.adapters;

import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.hospital.patient_management.application_logic.PatientManagementService;
import com.hospital.patient_management.domain.Patient;

@RestController
public class PatientRestController {

	@Autowired
	private PatientManagementService service;
	
	@RequestMapping(value="/patient", method=RequestMethod.GET)
	public Iterable<Patient> getPatients() {
		return service.findAll();
	}
	
	@RequestMapping(value="/patient/{id}", method=RequestMethod.GET)
	public Optional<Patient> findById(@PathVariable("id") String ssn) {
		return service.findById(ssn);
	}
	
	@RequestMapping(value="/patient/young_patients", method=RequestMethod.GET)
	public Iterable<Patient> getPatientsYoungerThan21(){
		return service.getPatientsYoungerThan(21);
	}
	
	@RequestMapping(value="/patient", method=RequestMethod.PUT)
	public void addPatient(@RequestBody Patient p) {
		service.addPatient(p);
	}
	
	@RequestMapping(value="/patient/search")
	public Iterable<Patient> getPatientsByFirstName(@RequestParam("name") String name) {
		return service.getPatientsByFirstName(name);
	}
}
