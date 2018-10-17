package be.ugent.student.reception.domain;


import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;

@Entity
public class HospitalStay {

	@Id @GeneratedValue
	private Long id;		
	private String patientId;	
	private Long wardId;	
	private Long bedId;	
	private Date dateOfStay;	
	private HospitalStayStatus status;
	

	public HospitalStay() {}
	
	public HospitalStay(String patientId, Long wardId, Date dateOfStay) {
		this.patientId = patientId;
		this.wardId = wardId;
		this.dateOfStay = dateOfStay;
		
		status = HospitalStayStatus.BOOKED;
	}
	
	
	
	
	@Override
    public String toString() {
        return String.format(
                "HospitalStay[id=%s, patientId='%s', wardId='%d', bedId='%d', dateOfStay='%s', status='%s']",
                id, patientId, wardId, bedId, dateOfStay, status);
    }
	
	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public String getPatientId() {
		return patientId;
	}

	public void setPatientId(String patientId) {
		this.patientId = patientId;
	}

	public Long getWardId() {
		return wardId;
	}

	public void setWardId(Long wardId) {
		this.wardId = wardId;
	}

	public Date getDateOfStay() {
		return dateOfStay;
	}

	public void setDateOfStay(Date dateOfStay) {
		this.dateOfStay = dateOfStay;
	}

	public HospitalStayStatus getStatus() {
		return status;
	}

	public void setStatus(HospitalStayStatus status) {
		this.status = status;
	}

	public Long getBedId() {
		return bedId;
	}

	public void setBedId(Long bedId) {
		this.bedId = bedId;
	}


}
