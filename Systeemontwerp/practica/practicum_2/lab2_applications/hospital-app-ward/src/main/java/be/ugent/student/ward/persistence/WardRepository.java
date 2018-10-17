package be.ugent.student.ward.persistence;

import org.springframework.data.repository.CrudRepository;

import be.ugent.student.ward.domain.Ward;


public interface WardRepository extends CrudRepository<Ward, Long>{

	int countByIdAndBedsPatientIdIsNull(Long id); 
}
