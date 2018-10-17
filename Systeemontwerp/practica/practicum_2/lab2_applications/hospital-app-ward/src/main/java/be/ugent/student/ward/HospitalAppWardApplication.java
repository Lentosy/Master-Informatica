package be.ugent.student.ward;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import be.ugent.student.ward.domain.Ward;
import be.ugent.student.ward.persistence.WardRepository;

@SpringBootApplication
public class HospitalAppWardApplication {

	private static final Logger log = LoggerFactory.getLogger(HospitalAppWardApplication.class);
	
	public static void main(String[] args) {
		SpringApplication.run(HospitalAppWardApplication.class, args);
	}
	
	
	@Bean
	public CommandLineRunner demo(WardRepository repository) {
		
		return (args) -> {			
			
			// save a couple of Wards
			repository.save(new Ward(2));
			repository.save(new Ward(2));
			Ward ward = new Ward(1); // no beds available on ward 3
			ward.assignBedToPaitent("10");
			repository.save(ward);


			log.info("-------------------------------");
			// fetch all Ward
			log.info("Ward found with findAll():");
			for (Ward result : repository.findAll()) {
				log.info(result.toString());
			}
			log.info("-------------------------------");
			
			// fetch number of free beds on Ward 1
			log.info("Beds with countByIdAndBedsPatientIdIsNull():" + repository.countByIdAndBedsPatientIdIsNull(1l));
			log.info("-------------------------------");			
		};
	}
}
