package be.ugent.student.ward.domain;

import java.util.ArrayList;
import java.util.List;

import javax.persistence.CascadeType;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.OneToMany;

//import com.fasterxml.jackson.annotation.JsonBackReference;

@Entity
public class Ward {
	@Id @GeneratedValue
	Long id;
	
	@OneToMany(cascade = CascadeType.ALL, mappedBy="ward", fetch = FetchType.EAGER)
	//@JsonBackReference // used to serialize entities with bidirectional relationships
	List<Bed> beds;
	
	public Ward(){ 
		beds = new ArrayList<Bed>();
	}
	
	
	public Ward(int numberOfBeds){
		beds = new ArrayList<Bed>();
		for (int i = 0; i < numberOfBeds; i++) {
			beds.add(new Bed(this));
		}
	}
	
	public Bed assignBedToPaitent(String patientId) { // example of an invariant: bed can only be assigned if it is unoccupied
		for(Bed bed : beds) {
			if(bed.getPatientId() == null) {
				bed.setPatientId(patientId);
				return bed;
			}
		}
		return null;
	}

	
	
	@Override
    public String toString() {
        return String.format(
                "ward[id=%d, beds='%s']",
                id, beds);
    }
	
	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}


	public List<Bed> getBeds() {
		return beds;
	}


	public void setBeds(List<Bed> beds) {
		this.beds = beds;
	}

}
