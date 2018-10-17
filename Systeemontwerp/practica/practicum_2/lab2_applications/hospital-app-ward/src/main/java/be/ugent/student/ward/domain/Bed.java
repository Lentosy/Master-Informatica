package be.ugent.student.ward.domain;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;

import org.hibernate.annotations.OnDelete;
import org.hibernate.annotations.OnDeleteAction;

//import com.fasterxml.jackson.annotation.JsonManagedReference;


@Entity
public class Bed {
	@Id @GeneratedValue
	Long id;
	
	String patientId = null;
	
	@ManyToOne(fetch = FetchType.LAZY, optional = false)
    @JoinColumn(name = "ward_id", nullable = false)
    @OnDelete(action = OnDeleteAction.CASCADE)
	//@JsonManagedReference // used to serialize entities with bidirectional relationships
    Ward ward;
	
	public Bed() {}
	
	public Bed(Ward ward) {
		this.ward = ward;
	}
	
	
	public Bed(String patientId) {
		this.patientId = patientId;
	}
	
	@Override
    public String toString() {
        return String.format(
                "bed[id=%d, occupied='%s']",
                id, patientId);
    }
	
	

	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public Ward getBed() {
		return ward;
	}


	public void setBed(Ward ward) {
		this.ward = ward;
	}

	public String getPatientId() {
		return patientId;
	}

	public void setPatientId(String patientId) {
		this.patientId = patientId;
	}

	
	public Ward getWard() {
		return ward;
	}

	
	public void setWard(Ward ward) {
		this.ward = ward;
	}

}
