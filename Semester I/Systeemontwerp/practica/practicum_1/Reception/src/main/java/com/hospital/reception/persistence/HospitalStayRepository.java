package com.hospital.reception.persistence;
import java.util.Optional;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;

import com.hospital.reception.domain.HospitalStay;

public interface HospitalStayRepository extends CrudRepository<HospitalStay, Long> {

	@Query("SELECT h FROM HospitalStay h WHERE h.patientId = :patientId AND h.status = com.hospital.reception.domain.Status.BOOKED")
	public Optional<HospitalStay> findPatientBooking(@Param("patientId") String patientId);
}
