package com.hospital.finance;

import java.util.ArrayList;
import java.util.Date;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import com.hospital.finance.domain.Invoice;
import com.hospital.finance.domain.ListItem;
import com.hospital.finance.domain.Status;
import com.hospital.finance.persistence.InvoiceRepository;



@SpringBootApplication
public class FinanceApplication {
	
	@Autowired
	InvoiceRepository repository;

	public static void main(String[] args) {
		SpringApplication.run(FinanceApplication.class, args);
	}
	
	
	@SuppressWarnings("serial")
	@Bean
	public void run() {
		Invoice i1 = new Invoice("1","123-456-789","1", new  Date(), Status.OPEN, new ArrayList<ListItem>() {
			{
				add(new ListItem("Item 1", 999.99));
				add(new ListItem("Item 2", 137.50));
			}
		});
		
		
		Invoice i2 = new Invoice("2","987-654-321","2", new  Date(), Status.OPEN, new ArrayList<ListItem>() {
			{
				add(new ListItem("Item 3", 1999.99));
				add(new ListItem("Item 4", 0.50));
			}
		});
		repository.deleteAll();
		
		repository.save(i1);
		repository.save(i2);
		
		System.out.println("Alle invoices:");
		repository.findAll().forEach(i -> System.out.println(i.toString()));
		

	
	}

}

