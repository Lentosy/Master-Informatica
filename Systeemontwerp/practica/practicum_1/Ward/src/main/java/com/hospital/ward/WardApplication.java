package com.hospital.ward;



import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import com.hospital.ward.domain.Ward;
import com.hospital.ward.persistence.BedRepository;

@SpringBootApplication
public class WardApplication {
	
	@Autowired 
	private BedRepository repository;

	public static void main(String[] args) {
		SpringApplication.run(WardApplication.class, args);
	
	}
	
	@Bean
	public void run() {
		
		Ward w1 = new Ward();
		w1.addBed(null);
		w1.addBed("1");
		w1.addBed(null);
		w1.addBed("2");
		w1.addBed(null);
	
		repository.save(w1);
		
		int unoccupiedbeds = repository.countUnoccupiedBedsForWard(w1.id);

	    System.out.println(String.format("%d unoccupied beds, expected 3", unoccupiedbeds));
		
	}

}

