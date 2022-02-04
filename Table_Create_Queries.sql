drop database save;
create database save;
use save;
create table accounts(
   first_name VARCHAR(50) NOT NULL,
   last_name VARCHAR(40) NOT NULL,
   street_address VARCHAR(100) NOT NULL,
   unit VARCHAR(10) NULL,
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
   merchant_number BIGINT NOT NULL,
   merchant_description VARCHAR(100) not null,
   merchant_category_code int not null,
   transaction_number int not null,
   PRIMARY KEY (transaction_id),
   FOREIGN KEY (account_number)
   references accounts(account_number)
);
select * from transactions;