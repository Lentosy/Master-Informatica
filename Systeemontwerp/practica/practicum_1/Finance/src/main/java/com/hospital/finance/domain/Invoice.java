package com.hospital.finance.domain;

import java.util.Date;
import java.util.List;

import org.springframework.data.mongodb.core.mapping.Document;

@Document
public class Invoice {

	public String invoiceId;
	public String patientId;
	public String hospitalStayId;
	
	public Date creationDate;
	
	public Status status;
	
	public List<ListItem> listItems;

	public Invoice(String invoiceId, String patientId, String hospitalStayId, Date creationDate, Status status,
			List<ListItem> listItems) {
		this.invoiceId = invoiceId;
		this.patientId = patientId;
		this.hospitalStayId = hospitalStayId;
		this.creationDate = creationDate;
		this.status = status;
		this.listItems = listItems;
	}
	
	@Override
	public String toString() {
		StringBuilder builder = new StringBuilder();
		builder.append(String.format("Invoice from %s on %s and status %s. Showing items:\n", patientId, creationDate.toString(), status));
		listItems.forEach(li -> {
			builder.append("\t");
			builder.append(li.toString());
			builder.append("\n");
		});
		return builder.toString();
	}
	
	
}
