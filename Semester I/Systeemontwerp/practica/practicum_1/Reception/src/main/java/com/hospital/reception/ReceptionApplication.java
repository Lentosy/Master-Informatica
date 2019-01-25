package com.hospital.reception;

import java.util.GregorianCalendar;
import java.util.Optional;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import com.hospital.reception.domain.HospitalStay;
import com.hospital.reception.domain.Status;
import com.hospital.reception.persistence.HospitalStayRepository;

@SpringBootApplication
public class ReceptionApplication {

	@Autowired
	HospitalStayRepository repository;

	public static void main(String[] args) {
		SpringApplication.run(ReceptionApplication.class, args);
	}
	
	
	@Bean
	public void run() {
		
		HospitalStay h1 = new HospitalStay("1","1",null, new GregorianCalendar().getTime(), Status.BOOKED);
		HospitalStay h2=  new HospitalStay("2","2",null, new GregorianCalendar().getTime(), Status.CHECKED_IN);
		HospitalStay h3 = new HospitalStay("3","3",null, new GregorianCalendar().getTime(), Status.CHECK_IN_PENDING);;
		
		repository.deleteAll();
		
		repository.save(h1);
		repository.save(h2);
		repository.save(h3);
		
		System.out.println("Alle HospitalStays:");
		repository.findAll().forEach(i -> System.out.println(i.toString()));
		
		System.out.println("Geboekte patiënten:");
		for(int i = 1; i <= 3; i++) {
			Optional<HospitalStay> hospitalStay = repository.findPatientBooking(Integer.toString(i));
			if(hospitalStay.isPresent()) {
				System.out.println(hospitalStay.get().toString());
			}else{
				System.out.println(String.format("Patient %d is nog niet geboekt", i));
			}
		
		}
		
		

	
	}

}

