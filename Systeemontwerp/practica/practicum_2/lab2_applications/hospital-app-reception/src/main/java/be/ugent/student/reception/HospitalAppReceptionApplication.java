package be.ugent.student.reception;

import java.util.Date;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import be.ugent.student.reception.domain.HospitalStay;
import be.ugent.student.reception.persistence.HospitalStayRepository;

/**
 * When running the full solution: 
 * 		patient 1 will be successfully checked in; 
 * 		an invoice will fail to be opened for patient 2;  
 * 		and for patient 3 a bed will failed to be assigned.
 * @author student
 *
 */
@SpringBootApplication
public class HospitalAppReceptionApplication {
	
	private static final Logger log = LoggerFactory.getLogger(HospitalAppReceptionApplication.class);


	public static void main(String[] args) {
		SpringApplication.run(HospitalAppReceptionApplication.class, args);
	}
	
	
	@Bean
	public CommandLineRunner demo(HospitalStayRepository repository) {
		
		return (args) -> {		
			
			// save a couple of HospitalStays
			repository.save(new HospitalStay("1", 1l, new Date()));
			repository.save(new HospitalStay("2", 2l, new Date()));
			repository.save(new HospitalStay("3", 3l, new Date()));


			log.info("-------------------------------");
			// fetch all HospitalStays
			log.info("HospitalStay found with findAll():");
			for (HospitalStay hospitalStay : repository.findAll()) {
				log.info(hospitalStay.toString());
			}
			log.info("-------------------------------");
			
			// fetch single booked HospitalStay for patient
			log.info("HospitalStay found with findByPaitentIdAndStatusBooked():");
			log.info(repository.findByPatientIdAndStatusBooked("2").toString());
			log.info("-------------------------------");						
		};
	}
}
