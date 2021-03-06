﻿USE master
GO
DROP DATABASE student
GO
CREATE DATABASE student
ON 
( NAME = Student_data,
   FILENAME = 'C:\tmp\student.mdf',
   SIZE = 1MB,
   MAXSIZE = 50MB,
   FILEGROWTH = 1MB )
LOG ON
( NAME = Student_log,
   FILENAME = 'C:\tmp\student.ldf',
   SIZE = 1MB,
   MAXSIZE = 50MB,
   FILEGROWTH = 1MB )
GO

USE student
GO
CREATE TABLE tb_student
(
	studentID		NCHAR(10) NOT NULL PRIMARY KEY CLUSTERED,
	studentName		NCHAR(8)        ,
	sex				NCHAR(2)            ,            
	telephone		NCHAR(20)	   ,
);
GO
CREATE TABLE tb_course
(
	courseID		NCHAR(10) NOT NULL PRIMARY KEY CLUSTERED,
	courseName		NCHAR(20) 
);
GO
CREATE TABLE tb_student_course
(
	courseID		NCHAR(10)  NOT NULL,
	studentID		NCHAR(10)  NOT NULL PRIMARY KEY(courseID, studentID),
	grade			int		 ,
	CONSTRAINT FK_tb_student_course 
			FOREIGN KEY (courseID) REFERENCES tb_course(courseID),
			FOREIGN KEY (studentID) REFERENCES tb_student(studentID),
	--CONSTRAINT PK_tb_student_course
	--		PRIMARY KEY(courseID, studentID)
);
GO
CREATE TABLE tb_class
(
	classID			NCHAR(10) NOT NULL PRIMARY KEY CLUSTERED,
	className		NCHAR(10),
);
GO
CREATE TABLE tb_student_class
(
	studentID		NCHAR(10) NOT NULL ,
	classID			NCHAR(10) NOT NULL PRIMARY KEY(studentID, classID),
	CONSTRAINT FK_tb_student_class 
			FOREIGN KEY (studentID) REFERENCES tb_student(studentID),
			FOREIGN KEY (classID) REFERENCES tb_class(classID),
	--CONSTRAINT PK_tb_student_class 
	--		PRIMARY KEY(studentID, classID)
);
GO

CREATE TABLE tb_update_time
(
	tableName				NCHAR(20) NOT NULL PRIMARY KEY CLUSTERED,
	updateTime				INT
)

INSERT INTO tb_student VALUES (721017,	N'韩璐冰',N'男',11234567890);
INSERT INTO tb_student VALUES (721025,	N'刘海江',N'男',12345678901);
INSERT INTO tb_student VALUES (721026,	N'刘凌君',N'男',13456789012);
INSERT INTO tb_student VALUES (721027,	N'刘宁琴',N'男',14567890123);
INSERT INTO tb_student VALUES (721039,	N'饶易宁',N'男',15678901234);
INSERT INTO tb_student VALUES (721021,	N'李好'  ,N'男',16789012345);
INSERT INTO tb_student VALUES (721052,	N'翟元浩',N'男',17890123456);
INSERT INTO tb_student VALUES (721044,	N'魏阳莉',N'男',18901234567);
INSERT INTO tb_student VALUES (721045,	N'吴金铃',N'男',19012345678);
INSERT INTO tb_student VALUES (721066,	N'刘畅'  ,N'男',10123456789);
INSERT INTO tb_student VALUES (721004,	N'陈恳'  ,N'男',21234567890);
INSERT INTO tb_student VALUES (721050,	N'余兴'  ,N'男',22345678901);
INSERT INTO tb_student VALUES (721038,	N'饶娜'  ,N'女',23456789012);
INSERT INTO tb_student VALUES (721015,	N'郭赛'  ,N'女',24567890123);
INSERT INTO tb_student VALUES (721043,	N'王炜'  ,N'女',25678901234);
INSERT INTO tb_student VALUES (721047,	N'夏朗明',N'女',26789012345);
INSERT INTO tb_student VALUES (721034,	N'梅智'  ,N'女',27890123456);
INSERT INTO tb_student VALUES (721035,	N'潘柏江',N'女',28901234567);
INSERT INTO tb_student VALUES (721020,	N'胡桐宇',N'女',29012345678);
INSERT INTO tb_student VALUES (721056,	N'张云翔',N'女',20123456789);
INSERT INTO tb_student VALUES (721033,	N'毛雨'  ,N'女',31234567890);
INSERT INTO tb_student VALUES (721006,	N'陈烨'  ,N'女',32345678901);
INSERT INTO tb_student VALUES (721031,	N'毛国卿',N'女',33456789012);
INSERT INTO tb_student VALUES (721023,	N'李子涵',N'男',34567890123);
INSERT INTO tb_student VALUES (721036,	N'彭若宁',N'男',35678901234);
INSERT INTO tb_student VALUES (721042,	N'王铭奇',N'男',36789012345);
INSERT INTO tb_student VALUES (721028,	N'刘焰颖',N'男',37890123456);
INSERT INTO tb_student VALUES (721037,	N'戚家铖',N'男',38901234567);
INSERT INTO tb_student VALUES (721011,	N'董哲'  ,N'男',39012345678);
INSERT INTO tb_student VALUES (721064,	N'朱胤熹',N'男',30123456789);
INSERT INTO tb_student VALUES (721030,	N'刘煜麟',N'男',41234567890);
INSERT INTO tb_student VALUES (721029,	N'刘益名',N'男',42345678901);
INSERT INTO tb_student VALUES (721058,	N'郑文鑫',N'男',43456789012);
INSERT INTO tb_student VALUES (721003,	N'查德平',N'男',44567890123);
INSERT INTO tb_student VALUES (721001,	N'蔡健'  ,N'女',45678901234);
INSERT INTO tb_student VALUES (721022,	N'李宇峰',N'女',46789012345);
INSERT INTO tb_student VALUES (721018,	N'何琪'  ,N'女',47890123456);
INSERT INTO tb_student VALUES (721024,	N'刘奥'  ,N'女',48901234567);
INSERT INTO tb_student VALUES (721012,	N'干玉兰',N'女',49012345678);
INSERT INTO tb_student VALUES (721010,	N'董亚坤',N'女',40123456789);
INSERT INTO tb_student VALUES (721013,	N'高炎鑫',N'女',51234567890);
INSERT INTO tb_student VALUES (721040,	N'田浩'  ,N'女',52345678901);
INSERT INTO tb_student VALUES (721060,	N'周康'  ,N'女',53456789012);
INSERT INTO tb_student VALUES (721046,	N'吴越'  ,N'女',54567890123);
INSERT INTO tb_student VALUES (721065,	N'朱梓铭',N'女',55678901234);
INSERT INTO tb_student VALUES (721049,	N'余晨'  ,N'男',56789012345);
INSERT INTO tb_student VALUES (721063,	N'朱平枫',N'男',57890123456);
INSERT INTO tb_student VALUES (721053,	N'詹哲凡',N'男',58901234567);
INSERT INTO tb_student VALUES (721057,	N'张子悦',N'男',59012345678);
INSERT INTO tb_student VALUES (721002,	N'蔡思斯',N'男',50123456789);
INSERT INTO tb_student VALUES (721041,	N'王靖飞',N'男',61234567890);
INSERT INTO tb_student VALUES (721016,	N'郭学哲',N'男',62345678901);
INSERT INTO tb_student VALUES (721048,	N'游佳莉',N'男',63456789012);
INSERT INTO tb_student VALUES (721051,	N'袁文海',N'女',64567890123);
INSERT INTO tb_student VALUES (721054,	N'张佳琪',N'女',65678901234);
INSERT INTO tb_student VALUES (721055,	N'张文杰',N'女',66789012345);
INSERT INTO tb_student VALUES (721007,	N'陈正桓',N'女',67890123456);
INSERT INTO tb_student VALUES (721005,	N'陈少卿',N'女',68901234567);
INSERT INTO tb_student VALUES (721032,	N'毛鹏锦',N'女',69012345678);
INSERT INTO tb_student VALUES (721059,	N'郑镇昊',N'女',60123456789);
INSERT INTO tb_student VALUES (721061,	N'周政宇',N'女',71234567890);
INSERT INTO tb_student VALUES (721014,	N'桂雨欣',N'女',72345678901);
INSERT INTO tb_student VALUES (721009,	N'董迅'  ,N'女',73456789012);
INSERT INTO tb_student VALUES (721019,	N'胡均盛',N'女',74567890123);
INSERT INTO tb_student VALUES (721008,	N'戴泽懿',N'女',75678901234);
INSERT INTO tb_student VALUES (721062,	N'朱博文',N'女',76789012345);
												
												
INSERT INTO tb_course VALUES (1, N'语文');		
INSERT INTO tb_course VALUES (2, N'数学');		
INSERT INTO tb_course VALUES (3, N'英语');
INSERT INTO tb_course VALUES (4, N'政治');
INSERT INTO tb_course VALUES (5, N'历史');
INSERT INTO tb_course VALUES (6, N'地理');
INSERT INTO tb_course VALUES (7, N'生物');



INSERT INTO tb_student_course VALUES(1, 721017, 106);
INSERT INTO tb_student_course VALUES(1, 721025, 95);
INSERT INTO tb_student_course VALUES(1, 721026, 96);
INSERT INTO tb_student_course VALUES(1, 721027, 92);
INSERT INTO tb_student_course VALUES(1, 721039, 99);
INSERT INTO tb_student_course VALUES(1, 721021, 91);
INSERT INTO tb_student_course VALUES(1, 721052, 92);
INSERT INTO tb_student_course VALUES(1, 721044, 97);
INSERT INTO tb_student_course VALUES(1, 721045, 94);
INSERT INTO tb_student_course VALUES(1, 721066, 91);
INSERT INTO tb_student_course VALUES(1, 721004, 92);
INSERT INTO tb_student_course VALUES(1, 721050, 94);
INSERT INTO tb_student_course VALUES(1, 721038, 97);
INSERT INTO tb_student_course VALUES(1, 721015, 95);
INSERT INTO tb_student_course VALUES(1, 721043, 91);
INSERT INTO tb_student_course VALUES(1, 721047, 89);
INSERT INTO tb_student_course VALUES(1, 721034, 91);
INSERT INTO tb_student_course VALUES(1, 721035, 95);
INSERT INTO tb_student_course VALUES(1, 721020, 98);
INSERT INTO tb_student_course VALUES(1, 721056, 84);
INSERT INTO tb_student_course VALUES(1, 721033, 94);
INSERT INTO tb_student_course VALUES(1, 721006, 92);
INSERT INTO tb_student_course VALUES(1, 721031, 92);
INSERT INTO tb_student_course VALUES(1, 721023, 87);
INSERT INTO tb_student_course VALUES(1, 721036, 90);
INSERT INTO tb_student_course VALUES(1, 721042, 95);
INSERT INTO tb_student_course VALUES(1, 721028, 92);
INSERT INTO tb_student_course VALUES(1, 721037, 97);
INSERT INTO tb_student_course VALUES(1, 721011, 91);
INSERT INTO tb_student_course VALUES(1, 721064, 88);
INSERT INTO tb_student_course VALUES(1, 721030, 86);
INSERT INTO tb_student_course VALUES(1, 721029, 87);
INSERT INTO tb_student_course VALUES(1, 721058, 102);
INSERT INTO tb_student_course VALUES(1, 721003, 80);
INSERT INTO tb_student_course VALUES(1, 721001, 86);
INSERT INTO tb_student_course VALUES(1, 721022, 94);
INSERT INTO tb_student_course VALUES(1, 721018, 82);
INSERT INTO tb_student_course VALUES(1, 721024, 86);
INSERT INTO tb_student_course VALUES(1, 721012, 86);
INSERT INTO tb_student_course VALUES(1, 721010, 86);
INSERT INTO tb_student_course VALUES(1, 721013, 91);
INSERT INTO tb_student_course VALUES(1, 721040, 96);
INSERT INTO tb_student_course VALUES(1, 721060, 86);
INSERT INTO tb_student_course VALUES(1, 721046, 89);
INSERT INTO tb_student_course VALUES(1, 721065, 88);
INSERT INTO tb_student_course VALUES(1, 721049, 88);
INSERT INTO tb_student_course VALUES(1, 721063, 89);
INSERT INTO tb_student_course VALUES(1, 721053, 86);
INSERT INTO tb_student_course VALUES(1, 721057, 88);
INSERT INTO tb_student_course VALUES(1, 721002, 86);
INSERT INTO tb_student_course VALUES(1, 721041, 75);
INSERT INTO tb_student_course VALUES(1, 721016, 89);
INSERT INTO tb_student_course VALUES(1, 721048, 79);
INSERT INTO tb_student_course VALUES(1, 721051, 73);
INSERT INTO tb_student_course VALUES(1, 721054, 69);
INSERT INTO tb_student_course VALUES(1, 721055, 73);
INSERT INTO tb_student_course VALUES(1, 721007, 90);
INSERT INTO tb_student_course VALUES(1, 721005, 79);
INSERT INTO tb_student_course VALUES(1, 721032, 88);
INSERT INTO tb_student_course VALUES(1, 721059, 80);
INSERT INTO tb_student_course VALUES(1, 721061, 86);
INSERT INTO tb_student_course VALUES(1, 721014, 76);
INSERT INTO tb_student_course VALUES(1, 721009, 64);
INSERT INTO tb_student_course VALUES(1, 721019, 73);
INSERT INTO tb_student_course VALUES(1, 721008, 43);
INSERT INTO tb_student_course VALUES(1, 721062, 73);


/*插入数学成绩*/
INSERT INTO tb_student_course VALUES(2, 721017, 120);
INSERT INTO tb_student_course VALUES(2, 721025, 115);
INSERT INTO tb_student_course VALUES(2, 721026, 106);
INSERT INTO tb_student_course VALUES(2, 721027, 104);
INSERT INTO tb_student_course VALUES(2, 721039, 110);
INSERT INTO tb_student_course VALUES(2, 721021, 114);
INSERT INTO tb_student_course VALUES(2, 721052, 101);
INSERT INTO tb_student_course VALUES(2, 721044, 98);
INSERT INTO tb_student_course VALUES(2, 721045, 104);
INSERT INTO tb_student_course VALUES(2, 721066, 94);
INSERT INTO tb_student_course VALUES(2, 721004, 90);
INSERT INTO tb_student_course VALUES(2, 721050, 108);
INSERT INTO tb_student_course VALUES(2, 721038, 91);
INSERT INTO tb_student_course VALUES(2, 721015, 102);
INSERT INTO tb_student_course VALUES(2, 721043, 105);
INSERT INTO tb_student_course VALUES(2, 721047, 110);
INSERT INTO tb_student_course VALUES(2, 721034, 107);
INSERT INTO tb_student_course VALUES(2, 721035, 96);
INSERT INTO tb_student_course VALUES(2, 721020, 81);
INSERT INTO tb_student_course VALUES(2, 721056, 111);
INSERT INTO tb_student_course VALUES(2, 721033, 95);
INSERT INTO tb_student_course VALUES(2, 721006, 104);
INSERT INTO tb_student_course VALUES(2, 721031, 97);
INSERT INTO tb_student_course VALUES(2, 721023, 93);
INSERT INTO tb_student_course VALUES(2, 721036, 102);
INSERT INTO tb_student_course VALUES(2, 721042, 107);
INSERT INTO tb_student_course VALUES(2, 721028, 107);
INSERT INTO tb_student_course VALUES(2, 721037, 94);
INSERT INTO tb_student_course VALUES(2, 721011, 92);
INSERT INTO tb_student_course VALUES(2, 721064, 113);
INSERT INTO tb_student_course VALUES(2, 721030, 92);
INSERT INTO tb_student_course VALUES(2, 721029, 108);
INSERT INTO tb_student_course VALUES(2, 721058, 80);
INSERT INTO tb_student_course VALUES(2, 721003, 92);
INSERT INTO tb_student_course VALUES(2, 721001, 105);
INSERT INTO tb_student_course VALUES(2, 721022, 77);
INSERT INTO tb_student_course VALUES(2, 721018, 98);
INSERT INTO tb_student_course VALUES(2, 721024, 105);
INSERT INTO tb_student_course VALUES(2, 721012, 85);
INSERT INTO tb_student_course VALUES(2, 721010, 85);
INSERT INTO tb_student_course VALUES(2, 721013, 79);
INSERT INTO tb_student_course VALUES(2, 721040, 92);
INSERT INTO tb_student_course VALUES(2, 721060, 86);
INSERT INTO tb_student_course VALUES(2, 721046, 59);
INSERT INTO tb_student_course VALUES(2, 721065, 92);
INSERT INTO tb_student_course VALUES(2, 721049, 68);
INSERT INTO tb_student_course VALUES(2, 721063, 78);
INSERT INTO tb_student_course VALUES(2, 721053, 78);
INSERT INTO tb_student_course VALUES(2, 721057, 52);
INSERT INTO tb_student_course VALUES(2, 721002, 54);
INSERT INTO tb_student_course VALUES(2, 721041, 80);
INSERT INTO tb_student_course VALUES(2, 721016, 27);
INSERT INTO tb_student_course VALUES(2, 721048, 102);
INSERT INTO tb_student_course VALUES(2, 721051, 22);
INSERT INTO tb_student_course VALUES(2, 721054, 59);
INSERT INTO tb_student_course VALUES(2, 721055, 82);
INSERT INTO tb_student_course VALUES(2, 721007, 43);
INSERT INTO tb_student_course VALUES(2, 721005, 71);
INSERT INTO tb_student_course VALUES(2, 721032, 29);
INSERT INTO tb_student_course VALUES(2, 721059, 7);
INSERT INTO tb_student_course VALUES(2, 721061, 32);
INSERT INTO tb_student_course VALUES(2, 721014, 40);
INSERT INTO tb_student_course VALUES(2, 721009, 37);
INSERT INTO tb_student_course VALUES(2, 721019, 32);
INSERT INTO tb_student_course VALUES(2, 721008, 40);
INSERT INTO tb_student_course VALUES(2, 721062, 28);

/*插入英语成绩*/
INSERT INTO tb_student_course VALUES(3, 721017, 118.5);
INSERT INTO tb_student_course VALUES(3, 721025, 117.5);
INSERT INTO tb_student_course VALUES(3, 721026, 114.5);
INSERT INTO tb_student_course VALUES(3, 721027, 117);
INSERT INTO tb_student_course VALUES(3, 721039, 112.5);
INSERT INTO tb_student_course VALUES(3, 721021, 115);
INSERT INTO tb_student_course VALUES(3, 721052, 113.5);
INSERT INTO tb_student_course VALUES(3, 721044, 114);
INSERT INTO tb_student_course VALUES(3, 721045, 114.5);
INSERT INTO tb_student_course VALUES(3, 721066, 113.5);
INSERT INTO tb_student_course VALUES(3, 721004, 120);
INSERT INTO tb_student_course VALUES(3, 721050, 110.5);
INSERT INTO tb_student_course VALUES(3, 721038, 109.5);
INSERT INTO tb_student_course VALUES(3, 721015, 109.5);
INSERT INTO tb_student_course VALUES(3, 721043, 111);
INSERT INTO tb_student_course VALUES(3, 721047, 112);
INSERT INTO tb_student_course VALUES(3, 721034, 102);
INSERT INTO tb_student_course VALUES(3, 721035, 116);
INSERT INTO tb_student_course VALUES(3, 721020, 108);
INSERT INTO tb_student_course VALUES(3, 721056, 113);
INSERT INTO tb_student_course VALUES(3, 721033, 116);
INSERT INTO tb_student_course VALUES(3, 721006, 112.5);
INSERT INTO tb_student_course VALUES(3, 721031, 114);
INSERT INTO tb_student_course VALUES(3, 721023, 112.5);
INSERT INTO tb_student_course VALUES(3, 721036, 113.5);
INSERT INTO tb_student_course VALUES(3, 721042, 96.5);
INSERT INTO tb_student_course VALUES(3, 721028, 112);
INSERT INTO tb_student_course VALUES(3, 721037, 107);
INSERT INTO tb_student_course VALUES(3, 721011, 110);
INSERT INTO tb_student_course VALUES(3, 721064, 104);
INSERT INTO tb_student_course VALUES(3, 721030, 114.5);
INSERT INTO tb_student_course VALUES(3, 721029, 94);
INSERT INTO tb_student_course VALUES(3, 721058, 106);
INSERT INTO tb_student_course VALUES(3, 721003, 109);
INSERT INTO tb_student_course VALUES(3, 721001, 103.5);
INSERT INTO tb_student_course VALUES(3, 721022, 101.5);
INSERT INTO tb_student_course VALUES(3, 721018, 107);
INSERT INTO tb_student_course VALUES(3, 721024, 111);
INSERT INTO tb_student_course VALUES(3, 721012, 97);
INSERT INTO tb_student_course VALUES(3, 721010, 108.5);
INSERT INTO tb_student_course VALUES(3, 721013, 108);
INSERT INTO tb_student_course VALUES(3, 721040, 83);
INSERT INTO tb_student_course VALUES(3, 721060, 109.5);
INSERT INTO tb_student_course VALUES(3, 721046, 94.5);
INSERT INTO tb_student_course VALUES(3, 721065, 87.5);
INSERT INTO tb_student_course VALUES(3, 721049, 109);
INSERT INTO tb_student_course VALUES(3, 721063, 100);
INSERT INTO tb_student_course VALUES(3, 721053, 103);
INSERT INTO tb_student_course VALUES(3, 721057, 102.5);
INSERT INTO tb_student_course VALUES(3, 721002, 100.5);
INSERT INTO tb_student_course VALUES(3, 721041, 87);
INSERT INTO tb_student_course VALUES(3, 721016, 103.5);
INSERT INTO tb_student_course VALUES(3, 721048, 30.5);
INSERT INTO tb_student_course VALUES(3, 721051, 104.5);
INSERT INTO tb_student_course VALUES(3, 721054, 86.5);
INSERT INTO tb_student_course VALUES(3, 721055, 52);
INSERT INTO tb_student_course VALUES(3, 721007, 79.5);
INSERT INTO tb_student_course VALUES(3, 721005, 59);
INSERT INTO tb_student_course VALUES(3, 721032, 74.5);
INSERT INTO tb_student_course VALUES(3, 721059, 90);
INSERT INTO tb_student_course VALUES(3, 721061, 53.5);
INSERT INTO tb_student_course VALUES(3, 721014, 67.5);
INSERT INTO tb_student_course VALUES(3, 721009, 73);
INSERT INTO tb_student_course VALUES(3, 721019, 53);
INSERT INTO tb_student_course VALUES(3, 721008, 66.5);
INSERT INTO tb_student_course VALUES(3, 721062, 40.5);

/*插入政治成绩*/
INSERT INTO tb_student_course VALUES(4, 721017, 30);
INSERT INTO tb_student_course VALUES(4, 721025, 28);
INSERT INTO tb_student_course VALUES(4, 721026, 37);
INSERT INTO tb_student_course VALUES(4, 721027, 33);
INSERT INTO tb_student_course VALUES(4, 721039, 27);
INSERT INTO tb_student_course VALUES(4, 721021, 37);
INSERT INTO tb_student_course VALUES(4, 721052, 27);
INSERT INTO tb_student_course VALUES(4, 721044, 37);
INSERT INTO tb_student_course VALUES(4, 721045, 25);
INSERT INTO tb_student_course VALUES(4, 721066, 30);
INSERT INTO tb_student_course VALUES(4, 721004, 29);
INSERT INTO tb_student_course VALUES(4, 721050, 27);
INSERT INTO tb_student_course VALUES(4, 721038, 28);
INSERT INTO tb_student_course VALUES(4, 721015, 23);
INSERT INTO tb_student_course VALUES(4, 721043, 21);
INSERT INTO tb_student_course VALUES(4, 721047, 25);
INSERT INTO tb_student_course VALUES(4, 721034, 23);
INSERT INTO tb_student_course VALUES(4, 721035, 24);
INSERT INTO tb_student_course VALUES(4, 721020, 27);
INSERT INTO tb_student_course VALUES(4, 721056, 18);
INSERT INTO tb_student_course VALUES(4, 721033, 27);
INSERT INTO tb_student_course VALUES(4, 721006, 20);
INSERT INTO tb_student_course VALUES(4, 721031, 22);
INSERT INTO tb_student_course VALUES(4, 721023, 30);
INSERT INTO tb_student_course VALUES(4, 721036, 23);
INSERT INTO tb_student_course VALUES(4, 721042, 25);
INSERT INTO tb_student_course VALUES(4, 721028, 22);
INSERT INTO tb_student_course VALUES(4, 721037, 24);
INSERT INTO tb_student_course VALUES(4, 721011, 27);
INSERT INTO tb_student_course VALUES(4, 721064, 20);
INSERT INTO tb_student_course VALUES(4, 721030, 23);
INSERT INTO tb_student_course VALUES(4, 721029, 22);
INSERT INTO tb_student_course VALUES(4, 721058, 29);
INSERT INTO tb_student_course VALUES(4, 721003, 23);
INSERT INTO tb_student_course VALUES(4, 721001, 23);
INSERT INTO tb_student_course VALUES(4, 721022, 30);
INSERT INTO tb_student_course VALUES(4, 721018, 21);
INSERT INTO tb_student_course VALUES(4, 721024, 19);
INSERT INTO tb_student_course VALUES(4, 721012, 29);
INSERT INTO tb_student_course VALUES(4, 721010, 25);
INSERT INTO tb_student_course VALUES(4, 721013, 28);
INSERT INTO tb_student_course VALUES(4, 721040, 26);
INSERT INTO tb_student_course VALUES(4, 721060, 18);
INSERT INTO tb_student_course VALUES(4, 721046, 24);
INSERT INTO tb_student_course VALUES(4, 721065, 22);
INSERT INTO tb_student_course VALUES(4, 721049, 25);
INSERT INTO tb_student_course VALUES(4, 721063, 15);
INSERT INTO tb_student_course VALUES(4, 721053, 16);
INSERT INTO tb_student_course VALUES(4, 721057, 22);
INSERT INTO tb_student_course VALUES(4, 721002, 28);
INSERT INTO tb_student_course VALUES(4, 721041, 16);
INSERT INTO tb_student_course VALUES(4, 721016, 25);
INSERT INTO tb_student_course VALUES(4, 721048, 12);
INSERT INTO tb_student_course VALUES(4, 721051, 22);
INSERT INTO tb_student_course VALUES(4, 721054, 21);
INSERT INTO tb_student_course VALUES(4, 721055, 23);
INSERT INTO tb_student_course VALUES(4, 721007, 18);
INSERT INTO tb_student_course VALUES(4, 721005, 13);
INSERT INTO tb_student_course VALUES(4, 721032, 18);
INSERT INTO tb_student_course VALUES(4, 721059, 20);
INSERT INTO tb_student_course VALUES(4, 721061, 21);
INSERT INTO tb_student_course VALUES(4, 721014, 20);
INSERT INTO tb_student_course VALUES(4, 721009, 18);
INSERT INTO tb_student_course VALUES(4, 721019, 16);
INSERT INTO tb_student_course VALUES(4, 721008, 10);
INSERT INTO tb_student_course VALUES(4, 721062, 24);

/*插入历史成绩*/
INSERT INTO tb_student_course VALUES(5, 721017, 32);
INSERT INTO tb_student_course VALUES(5, 721025, 34);
INSERT INTO tb_student_course VALUES(5, 721026, 35);
INSERT INTO tb_student_course VALUES(5, 721027, 28);
INSERT INTO tb_student_course VALUES(5, 721039, 29);
INSERT INTO tb_student_course VALUES(5, 721021, 25);
INSERT INTO tb_student_course VALUES(5, 721052, 34);
INSERT INTO tb_student_course VALUES(5, 721044, 23);
INSERT INTO tb_student_course VALUES(5, 721045, 28);
INSERT INTO tb_student_course VALUES(5, 721066, 30);
INSERT INTO tb_student_course VALUES(5, 721004, 32);
INSERT INTO tb_student_course VALUES(5, 721050, 33);
INSERT INTO tb_student_course VALUES(5, 721038, 27);
INSERT INTO tb_student_course VALUES(5, 721015, 29);
INSERT INTO tb_student_course VALUES(5, 721043, 31);
INSERT INTO tb_student_course VALUES(5, 721047, 24);
INSERT INTO tb_student_course VALUES(5, 721034, 31);
INSERT INTO tb_student_course VALUES(5, 721035, 23);
INSERT INTO tb_student_course VALUES(5, 721020, 30);
INSERT INTO tb_student_course VALUES(5, 721056, 26);
INSERT INTO tb_student_course VALUES(5, 721033, 25);
INSERT INTO tb_student_course VALUES(5, 721006, 30);
INSERT INTO tb_student_course VALUES(5, 721031, 28);
INSERT INTO tb_student_course VALUES(5, 721023, 35);
INSERT INTO tb_student_course VALUES(5, 721036, 28);
INSERT INTO tb_student_course VALUES(5, 721042, 26);
INSERT INTO tb_student_course VALUES(5, 721028, 19);
INSERT INTO tb_student_course VALUES(5, 721037, 24);
INSERT INTO tb_student_course VALUES(5, 721011, 18);
INSERT INTO tb_student_course VALUES(5, 721064, 23);
INSERT INTO tb_student_course VALUES(5, 721030, 24);
INSERT INTO tb_student_course VALUES(5, 721029, 19);
INSERT INTO tb_student_course VALUES(5, 721058, 30);
INSERT INTO tb_student_course VALUES(5, 721003, 24);
INSERT INTO tb_student_course VALUES(5, 721001, 23);
INSERT INTO tb_student_course VALUES(5, 721022, 24);
INSERT INTO tb_student_course VALUES(5, 721018, 24);
INSERT INTO tb_student_course VALUES(5, 721024, 17);
INSERT INTO tb_student_course VALUES(5, 721012, 18);
INSERT INTO tb_student_course VALUES(5, 721010, 19);
INSERT INTO tb_student_course VALUES(5, 721013, 9);
INSERT INTO tb_student_course VALUES(5, 721040, 24);
INSERT INTO tb_student_course VALUES(5, 721060, 18);
INSERT INTO tb_student_course VALUES(5, 721046, 31);
INSERT INTO tb_student_course VALUES(5, 721065, 20);
INSERT INTO tb_student_course VALUES(5, 721049, 19);
INSERT INTO tb_student_course VALUES(5, 721063, 21);
INSERT INTO tb_student_course VALUES(5, 721053, 16);
INSERT INTO tb_student_course VALUES(5, 721057, 23);
INSERT INTO tb_student_course VALUES(5, 721002, 13);
INSERT INTO tb_student_course VALUES(5, 721041, 21);
INSERT INTO tb_student_course VALUES(5, 721016, 14);
INSERT INTO tb_student_course VALUES(5, 721048, 27);
INSERT INTO tb_student_course VALUES(5, 721051, 22);
INSERT INTO tb_student_course VALUES(5, 721054, 16);
INSERT INTO tb_student_course VALUES(5, 721055, 21);
INSERT INTO tb_student_course VALUES(5, 721007, 13);
INSERT INTO tb_student_course VALUES(5, 721005, 20);
INSERT INTO tb_student_course VALUES(5, 721032, 24);
INSERT INTO tb_student_course VALUES(5, 721059, 24);
INSERT INTO tb_student_course VALUES(5, 721061, 19);
INSERT INTO tb_student_course VALUES(5, 721014, 15);
INSERT INTO tb_student_course VALUES(5, 721009, 16);
INSERT INTO tb_student_course VALUES(5, 721019, 21);
INSERT INTO tb_student_course VALUES(5, 721008, 16);
INSERT INTO tb_student_course VALUES(5, 721062, 15);

/*插入地理成绩*/
INSERT INTO tb_student_course VALUES(6, 721017, 15);
INSERT INTO tb_student_course VALUES(6, 721025, 20);
INSERT INTO tb_student_course VALUES(6, 721026, 14);
INSERT INTO tb_student_course VALUES(6, 721027, 21);
INSERT INTO tb_student_course VALUES(6, 721039, 17);
INSERT INTO tb_student_course VALUES(6, 721021, 13);
INSERT INTO tb_student_course VALUES(6, 721052, 13);
INSERT INTO tb_student_course VALUES(6, 721044, 15);
INSERT INTO tb_student_course VALUES(6, 721045, 17);
INSERT INTO tb_student_course VALUES(6, 721066, 21);
INSERT INTO tb_student_course VALUES(6, 721004, 18);
INSERT INTO tb_student_course VALUES(6, 721050, 11);
INSERT INTO tb_student_course VALUES(6, 721038, 16);
INSERT INTO tb_student_course VALUES(6, 721015, 13);
INSERT INTO tb_student_course VALUES(6, 721043, 15);
INSERT INTO tb_student_course VALUES(6, 721047, 16);
INSERT INTO tb_student_course VALUES(6, 721034, 12);
INSERT INTO tb_student_course VALUES(6, 721035, 14);
INSERT INTO tb_student_course VALUES(6, 721020, 21);
INSERT INTO tb_student_course VALUES(6, 721056, 15);
INSERT INTO tb_student_course VALUES(6, 721033, 5);
INSERT INTO tb_student_course VALUES(6, 721006, 9);
INSERT INTO tb_student_course VALUES(6, 721031, 13);
INSERT INTO tb_student_course VALUES(6, 721023, 5);
INSERT INTO tb_student_course VALUES(6, 721036, 9);
INSERT INTO tb_student_course VALUES(6, 721042, 13);
INSERT INTO tb_student_course VALUES(6, 721028, 12);
INSERT INTO tb_student_course VALUES(6, 721037, 12);
INSERT INTO tb_student_course VALUES(6, 721011, 15);
INSERT INTO tb_student_course VALUES(6, 721064, 11);
INSERT INTO tb_student_course VALUES(6, 721030, 14);
INSERT INTO tb_student_course VALUES(6, 721029, 16);
INSERT INTO tb_student_course VALUES(6, 721058, 5);
INSERT INTO tb_student_course VALUES(6, 721003, 14);
INSERT INTO tb_student_course VALUES(6, 721001, 12);
INSERT INTO tb_student_course VALUES(6, 721022, 15);
INSERT INTO tb_student_course VALUES(6, 721018, 7);
INSERT INTO tb_student_course VALUES(6, 721024, 6);
INSERT INTO tb_student_course VALUES(6, 721012, 15);
INSERT INTO tb_student_course VALUES(6, 721010, 8);
INSERT INTO tb_student_course VALUES(6, 721013, 9);
INSERT INTO tb_student_course VALUES(6, 721040, 8);
INSERT INTO tb_student_course VALUES(6, 721060, 8);
INSERT INTO tb_student_course VALUES(6, 721046, 8);
INSERT INTO tb_student_course VALUES(6, 721065, 11);
INSERT INTO tb_student_course VALUES(6, 721049, 11);
INSERT INTO tb_student_course VALUES(6, 721063, 10);
INSERT INTO tb_student_course VALUES(6, 721053, 7);
INSERT INTO tb_student_course VALUES(6, 721057, 12);
INSERT INTO tb_student_course VALUES(6, 721002, 12);
INSERT INTO tb_student_course VALUES(6, 721041, 12);
INSERT INTO tb_student_course VALUES(6, 721016, 9);
INSERT INTO tb_student_course VALUES(6, 721048, 9);
INSERT INTO tb_student_course VALUES(6, 721051, 8);
INSERT INTO tb_student_course VALUES(6, 721054, 6);
INSERT INTO tb_student_course VALUES(6, 721055, 7);
INSERT INTO tb_student_course VALUES(6, 721007, 7);
INSERT INTO tb_student_course VALUES(6, 721005, 9);
INSERT INTO tb_student_course VALUES(6, 721032, 7);
INSERT INTO tb_student_course VALUES(6, 721059, 9);
INSERT INTO tb_student_course VALUES(6, 721061, 10);
INSERT INTO tb_student_course VALUES(6, 721014, 5);
INSERT INTO tb_student_course VALUES(6, 721009, 9);
INSERT INTO tb_student_course VALUES(6, 721019, 6);
INSERT INTO tb_student_course VALUES(6, 721008, 7);
INSERT INTO tb_student_course VALUES(6, 721062, 8);


/*插入生物成绩*/
INSERT INTO tb_student_course VALUES(7, 721017, 15);
INSERT INTO tb_student_course VALUES(7, 721025, 23);
INSERT INTO tb_student_course VALUES(7, 721026, 21);
INSERT INTO tb_student_course VALUES(7, 721027, 24);
INSERT INTO tb_student_course VALUES(7, 721039, 21);
INSERT INTO tb_student_course VALUES(7, 721021, 20);
INSERT INTO tb_student_course VALUES(7, 721052, 28);
INSERT INTO tb_student_course VALUES(7, 721044, 23);
INSERT INTO tb_student_course VALUES(7, 721045, 21);
INSERT INTO tb_student_course VALUES(7, 721066, 24);
INSERT INTO tb_student_course VALUES(7, 721004, 18);
INSERT INTO tb_student_course VALUES(7, 721050, 11);
INSERT INTO tb_student_course VALUES(7, 721038, 25);
INSERT INTO tb_student_course VALUES(7, 721015, 20);
INSERT INTO tb_student_course VALUES(7, 721043, 14);
INSERT INTO tb_student_course VALUES(7, 721047, 12);
INSERT INTO tb_student_course VALUES(7, 721034, 18);
INSERT INTO tb_student_course VALUES(7, 721035, 16);
INSERT INTO tb_student_course VALUES(7, 721020, 18);
INSERT INTO tb_student_course VALUES(7, 721056, 16);
INSERT INTO tb_student_course VALUES(7, 721033, 19);
INSERT INTO tb_student_course VALUES(7, 721006, 13);
INSERT INTO tb_student_course VALUES(7, 721031, 14);
INSERT INTO tb_student_course VALUES(7, 721023, 15);
INSERT INTO tb_student_course VALUES(7, 721036, 12);
INSERT INTO tb_student_course VALUES(7, 721042, 13);
INSERT INTO tb_student_course VALUES(7, 721028, 11);
INSERT INTO tb_student_course VALUES(7, 721037, 17);
INSERT INTO tb_student_course VALUES(7, 721011, 17);
INSERT INTO tb_student_course VALUES(7, 721064, 11);
INSERT INTO tb_student_course VALUES(7, 721030, 15);
INSERT INTO tb_student_course VALUES(7, 721029, 22);
INSERT INTO tb_student_course VALUES(7, 721058, 13);
INSERT INTO tb_student_course VALUES(7, 721003, 20);
INSERT INTO tb_student_course VALUES(7, 721001, 9);
INSERT INTO tb_student_course VALUES(7, 721022, 13);
INSERT INTO tb_student_course VALUES(7, 721018, 13);
INSERT INTO tb_student_course VALUES(7, 721024, 4);
INSERT INTO tb_student_course VALUES(7, 721012, 13);
INSERT INTO tb_student_course VALUES(7, 721010, 9);
INSERT INTO tb_student_course VALUES(7, 721013, 14);
INSERT INTO tb_student_course VALUES(7, 721040, 9);
INSERT INTO tb_student_course VALUES(7, 721060, 7);
INSERT INTO tb_student_course VALUES(7, 721046, 24);
INSERT INTO tb_student_course VALUES(7, 721065, 8);
INSERT INTO tb_student_course VALUES(7, 721049, 8);
INSERT INTO tb_student_course VALUES(7, 721063, 12);
INSERT INTO tb_student_course VALUES(7, 721053, 11);
INSERT INTO tb_student_course VALUES(7, 721057, 14);
INSERT INTO tb_student_course VALUES(7, 721002, 8);
INSERT INTO tb_student_course VALUES(7, 721041, 9);
INSERT INTO tb_student_course VALUES(7, 721016, 14);
INSERT INTO tb_student_course VALUES(7, 721048, 22);
INSERT INTO tb_student_course VALUES(7, 721051, 15);
INSERT INTO tb_student_course VALUES(7, 721054, 8);
INSERT INTO tb_student_course VALUES(7, 721055, 7);
INSERT INTO tb_student_course VALUES(7, 721007, 11);
INSERT INTO tb_student_course VALUES(7, 721005, 9);
INSERT INTO tb_student_course VALUES(7, 721032, 8);
INSERT INTO tb_student_course VALUES(7, 721059, 17);
INSERT INTO tb_student_course VALUES(7, 721061, 12);
INSERT INTO tb_student_course VALUES(7, 721014, 5);
INSERT INTO tb_student_course VALUES(7, 721009, 7);
INSERT INTO tb_student_course VALUES(7, 721019, 8);
INSERT INTO tb_student_course VALUES(7, 721008, 16);
INSERT INTO tb_student_course VALUES(7, 721062, 5)


INSERT INTO tb_class VALUES(1, 1);
INSERT INTO tb_class VALUES(2, 2);
INSERT INTO tb_class VALUES(3, 3);
INSERT INTO tb_class VALUES(4, 4);


INSERT INTO tb_student_class VALUES(721017,  1);
INSERT INTO tb_student_class VALUES(721025,  1);
INSERT INTO tb_student_class VALUES(721026,  1);
INSERT INTO tb_student_class VALUES(721027,  1);
INSERT INTO tb_student_class VALUES(721039,  1);
INSERT INTO tb_student_class VALUES(721021,  1);
INSERT INTO tb_student_class VALUES(721052,  1);
INSERT INTO tb_student_class VALUES(721044,  1);
INSERT INTO tb_student_class VALUES(721045,  1);
INSERT INTO tb_student_class VALUES(721066,  1);
INSERT INTO tb_student_class VALUES(721004,  1);
INSERT INTO tb_student_class VALUES(721050,  1);
INSERT INTO tb_student_class VALUES(721038,  1);
INSERT INTO tb_student_class VALUES(721015,  1);
INSERT INTO tb_student_class VALUES(721043,  1);
INSERT INTO tb_student_class VALUES(721047,  1);
INSERT INTO tb_student_class VALUES(721034,  1);
INSERT INTO tb_student_class VALUES(721035,  1);
INSERT INTO tb_student_class VALUES(721020,  1);
INSERT INTO tb_student_class VALUES(721056,  1);
INSERT INTO tb_student_class VALUES(721033,  1);
INSERT INTO tb_student_class VALUES(721006,  1);
INSERT INTO tb_student_class VALUES(721031,  1);
INSERT INTO tb_student_class VALUES(721023,  1);
INSERT INTO tb_student_class VALUES(721036,  1);
INSERT INTO tb_student_class VALUES(721042,  1);
INSERT INTO tb_student_class VALUES(721028,  2);
INSERT INTO tb_student_class VALUES(721037,  2);
INSERT INTO tb_student_class VALUES(721011,  2);
INSERT INTO tb_student_class VALUES(721064,  2);
INSERT INTO tb_student_class VALUES(721030,  2);
INSERT INTO tb_student_class VALUES(721029,  2);
INSERT INTO tb_student_class VALUES(721058,  2);
INSERT INTO tb_student_class VALUES(721003,  2);
INSERT INTO tb_student_class VALUES(721001,  2);
INSERT INTO tb_student_class VALUES(721022,  2);
INSERT INTO tb_student_class VALUES(721018,  2);
INSERT INTO tb_student_class VALUES(721024,  2);
INSERT INTO tb_student_class VALUES(721012,  2);
INSERT INTO tb_student_class VALUES(721010,  2);
INSERT INTO tb_student_class VALUES(721013,  2);
INSERT INTO tb_student_class VALUES(721040,  2);
INSERT INTO tb_student_class VALUES(721060,  2);
INSERT INTO tb_student_class VALUES(721046,  2);
INSERT INTO tb_student_class VALUES(721065,  2);
INSERT INTO tb_student_class VALUES(721049,  2);
INSERT INTO tb_student_class VALUES(721063,  2);
INSERT INTO tb_student_class VALUES(721053,  3);
INSERT INTO tb_student_class VALUES(721057,  3);
INSERT INTO tb_student_class VALUES(721002,  3);
INSERT INTO tb_student_class VALUES(721041,  3);
INSERT INTO tb_student_class VALUES(721016,  3);
INSERT INTO tb_student_class VALUES(721048,  3);
INSERT INTO tb_student_class VALUES(721051,  3);
INSERT INTO tb_student_class VALUES(721054,  3);
INSERT INTO tb_student_class VALUES(721055,  3);
INSERT INTO tb_student_class VALUES(721007,  3);
INSERT INTO tb_student_class VALUES(721005,  3);
INSERT INTO tb_student_class VALUES(721032,  4);
INSERT INTO tb_student_class VALUES(721059,  4);
INSERT INTO tb_student_class VALUES(721061,  4);
INSERT INTO tb_student_class VALUES(721014,  4);
INSERT INTO tb_student_class VALUES(721009,  4);
INSERT INTO tb_student_class VALUES(721019,  4);
INSERT INTO tb_student_class VALUES(721008,  4);
INSERT INTO tb_student_class VALUES(721062,  4);


INSERT INTO tb_update_time VALUES(N'updateTime',  0);

