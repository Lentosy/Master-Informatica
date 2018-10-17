package be.ugent.student.reception.application_logic;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import org.springframework.web.bind.annotation.RequestParam;

import be.ugent.student.reception.domain.HospitalStay;
import be.ugent.student.reception.persistence.HospitalStayRepository;

@Component
public class ReceptionService {
	@Autowired
	private HospitalStayRepository hospitalStayRepository;
		
	
	//----------------------------------------
	//------       Lab session 1        ------
    public Iterable<HospitalStay> getHospitalStays() {
        return hospitalStayRepository.findAll();
    }
	
	public HospitalStay getPatientBooking(@RequestParam String patientId) {
		return hospitalStayRepository.findByPatientIdAndStatusBooked(patientId);				
	}
	//------------------------------------------
	
	
	
	
	
}
