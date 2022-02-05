/*drop database save;
create database save;
use save;
create table accounts(
   first_name VARCHAR(50) NOT NULL,
   last_name VARCHAR(40) NOT NULL,
   street_address VARCHAR(100) NOT NULL,
   unit smallint NULL,
   city VARCHAR(20) NOT NULL,
   state VARCHAR(5) NOT NULL,
   zip VARCHAR(8) NOT NULL,
   dob DATE,
   ssn VARCHAR(15) NOT NULL,
   email_address VARCHAR(40) NOT NULL,
   mobile_number BIGINT NOT NULL,
   account_number INT NOT NULL,
   PRIMARY KEY (account_number)   
);

show tables;
select * from accounts;

create table transactions(
   transaction_id int AUTO_INCREMENT,
   account_number INT NOT NULL,
   transaction_datetime datetime not null,
   transaction_amount float not null, 
   post_date date not null,
   merchant_number VARCHAR(20) NOT NULL,
   merchant_description VARCHAR(100) not null,
   merchant_category_code int not null,
   transaction_number int not null,
   PRIMARY KEY (transaction_id),
   FOREIGN KEY (account_number)
   references accounts(account_number)
);
select * from transactions;


insert into accounts (first_name, last_name, street_address, unit, city, state, zip, dob, ssn, email_address, mobile_number, account_number) 
values ("a", "b", "aa", 1, "a", "b", "2", "2019-10-12", "100000", "abc@abc.com", 129399, 1222);

select * from accounts;


insert into transactions (account_number, transaction_datetime, transaction_amount, post_date, merchant_number, merchant_description, merchant_category_code, transaction_number) 
values (1222, "2010-12-12 21:10:10", 100.100, "2010-10-10", 10000, "DEF", 1000, 1000);

select * from transactions;
*/