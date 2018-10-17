package be.ugent.student.reception.adpters.handlers;

import java.util.HashMap;
import java.util.Map;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.context.request.async.DeferredResult;

import be.ugent.student.reception.application_logic.ReceptionService;
import be.ugent.student.reception.domain.HospitalStay;

@RestController
public class ReceptionRestController {
	
	
	//----------------------------------------
	//------       Lab session 1        ------
	
	@Autowired
	ReceptionService reception;
	
	
	// http://localhost:2223/reception/hospital_stays
	@RequestMapping(value="/reception/hospital_stays", method=RequestMethod.GET)
    public Iterable<HospitalStay> getHospitalStays() {
        return reception.getHospitalStays();
    }
	
	// http://localhost:2223/reception/get_patient_booking?patientId=1
	@RequestMapping(value="/reception/get_patient_booking")
	public HospitalStay getPatientBooking(@RequestParam String patientId) {			
		return reception.getPatientBooking(patientId);
	}
	
	
	
	//--------------------------------------------------------
	//------       Lab session 2  : starting point      ------	
	

	Map<String, DeferredResult<HospitalStay>> deferredResults = new HashMap<String, DeferredResult<HospitalStay>>();
	
	// http://localhost:2223/reception/check_in_patient?patientId=1
	@RequestMapping(value="/reception/check_in_patient")
	public DeferredResult<HospitalStay> handlePatientCheckIn(@RequestParam String patientId) {		
		DeferredResult<HospitalStay> deferredResult = new DeferredResult<>(10000l);
		deferredResult.onTimeout(() ->  deferredResult.setErrorResult("Request timeout occurred."));
		deferredResults.put(patientId, deferredResult); // we will use patientId as a unique value
				
		/*try {
		
			//call your service class (saga) here
			 
		} catch (BookedHospitalStayNotFoundException e) {
			deferredResults.remove(patientId); 
			deferredResult.setErrorResult("Failed to check-in patient. " + e.getMessage());
		}*/
		
		return deferredResult;
	}
	
	//Sends result to client after patient has been assigned a bed, and an invoice has been opened.
	public void performResponse(HospitalStay response) {
		DeferredResult<HospitalStay> deferredResult = deferredResults.remove(response.getPatientId());
		if ((deferredResult != null) && !deferredResult.isSetOrExpired()) {
			deferredResult.setResult(response);
		}
	}
	
	//--------------------------------------------------------
	
}

