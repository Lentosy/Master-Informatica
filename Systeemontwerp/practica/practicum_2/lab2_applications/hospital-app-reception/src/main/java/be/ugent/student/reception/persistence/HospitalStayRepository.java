package be.ugent.student.reception.persistence;


import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.reactive.ReactiveCrudRepository;

import be.ugent.student.reception.domain.HospitalStay;

public interface HospitalStayRepository extends CrudRepository<HospitalStay, Long> {//ReactiveCrudRepository<HospitalStay, Long> { //

	@Query("SELECT h FROM HospitalStay h WHERE patientId = ?1 AND status = be.ugent.student.reception.domain.HospitalStayStatus.BOOKED")
	HospitalStay findByPatientIdAndStatusBooked(String patientId);
	
	//@Query("SELECT h FROM HospitalStay h WHERE h.patientId = ?1)")
	HospitalStay findByPatientId(String patientId);
}
