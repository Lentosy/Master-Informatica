create table auction (
    id int NOT NULL GENERATED ALWAYS AS IDENTITY CONSTRAINT QUESTION_PK PRIMARY KEY,
    description varchar(500) NOT NULL,
    minprice double NOT NULL
);