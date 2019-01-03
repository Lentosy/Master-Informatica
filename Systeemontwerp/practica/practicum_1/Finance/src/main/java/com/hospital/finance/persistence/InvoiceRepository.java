package com.hospital.finance.persistence;



import com.hospital.finance.domain.Invoice;
import org.springframework.data.mongodb.repository.MongoRepository;
public interface InvoiceRepository extends MongoRepository<Invoice, String>{

}
