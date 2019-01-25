package com.hospital.ward.persistence;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.repository.query.Param;

import com.hospital.ward.domain.Ward;

public interface BedRepository extends CrudRepository<Ward, Long>{
	
	@Query("SELECT COUNT(w.id) FROM Ward w JOIN Bed b ON w.id = b.ward WHERE b.patientId = NULL")
	int countUnoccupiedBedsForWard(@Param("wardId") long wardId);


}
