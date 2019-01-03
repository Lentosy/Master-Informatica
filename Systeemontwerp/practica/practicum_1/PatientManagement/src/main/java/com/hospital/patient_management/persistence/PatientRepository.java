package com.hospital.patient_management.persistence;

import java.util.List;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;

import com.hospital.patient_management.domain.Patient;


public interface PatientRepository extends CrudRepository<Patient, String> {
	List<Patient> getPatientsByFirstName(String firstName);
	
	@Query("SELECT p FROM Patient p WHERE p.firstName LIKE :letter%")
	List<Patient> getPatientsByLetter(@Param("letter")String letter);
	
	@Query("SELECT p FROM Patient p WHERE TIMESTAMPDIFF(year, p.dateOfBirth, NOW()) < :age")
	List<Patient> getPatientsYoungerThan(@Param("age") int age);
}
