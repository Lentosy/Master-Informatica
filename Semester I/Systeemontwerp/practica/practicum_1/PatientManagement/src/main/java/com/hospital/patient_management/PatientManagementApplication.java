package com.hospital.patient_management;

import java.util.GregorianCalendar;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import com.hospital.patient_management.domain.Patient;
import com.hospital.patient_management.persistence.PatientRepository;

@SpringBootApplication
public class PatientManagementApplication {
	
	@Autowired
	PatientRepository repository;

	public static void main(String[] args) {
		SpringApplication.run(PatientManagementApplication.class, args);
	}
	
	
	@Bean
	public void run() {
		Patient bert = new Patient("123-456-789", "Bert", "De Saffel", new GregorianCalendar(1995, 9, 13).getTime());
		Patient xandro = new Patient("987-654-321", "Xandro", "Vermeulen", new GregorianCalendar(1995, 11, 26).getTime());
		Patient senne = new Patient("111-222-333", "Senne", "De Saffel", new GregorianCalendar(2002, 8, 6).getTime());
		Patient jelle = new Patient("444-555-666", "Jelle", "De Vlieger", new GregorianCalendar(1989, 2, 23).getTime());
		repository.save(bert);
		repository.save(xandro);
		repository.save(senne);
		repository.save(jelle);
		
		System.out.println("Alle patiënten:");
		repository.findAll().forEach(p -> System.out.println(p.toString()));
		
		System.out.println("Patiënt met ssn = 123-456-789");
		System.out.println(repository.findById("123-456-789").get().toString());
		
		System.out.println("Patiënten met voornaam = Xandro");
		repository.getPatientsByFirstName("Xandro").forEach(p -> System.out.println(p.toString()));
		
		System.out.println("Patiënten jonger dan 21 jaar");
		repository.getPatientsYoungerThan(21).forEach(p -> System.out.println(p.toString()));
		
		System.out.println("Patiënten waarvan de voornaam start met J:");
		repository.getPatientsByLetter("J").forEach(p -> System.out.println(p.toString()));
	}

}

