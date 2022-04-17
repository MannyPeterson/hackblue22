CREATE USER ubuntu@localhost IDENTIFIED BY 'fuzzer';
GRANT ALL ON *.* TO ubuntu@localhost WITH GRANT OPTION;
CREATE DATABASE hackblue22;
USE hackblue22;
CREATE TABLE hackblue22.events(
	event_id INT NOT NULL AUTO_INCREMENT,
	customer_id VARCHAR(32),
	product_id VARCHAR(32),
	serial_no VARCHAR(32),
	temperature DECIMAL(8,4),
	created TIMESTAMP,
	PRIMARY KEY(event_id)
);
CREATE USER hackblue22@localhost IDENTIFIED BY 'fuzzer';
GRANT SELECT, INSERT ON hackblue22.events TO hackblue22@localhost;
