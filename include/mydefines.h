#pragma once

enum class SelectTable
{
	tb_student,
	tb_course,
	tb_class,
	tb_studentCourse,
	tb_studentClass
};

enum class SelectKey
{
	studentID,
	studentName,
	sex,
	telephone,
	courseID,
	courseName,
	grade,
	classID,
	className,
};

extern const char* strTables[];
extern const char* strKeyNames[];
extern const char* strKeyNamesWithTable[];

enum class MessageType
{
	Nop,
	NoServer,

	AskSC,
	AnsServer,
	AnsClient,

	Add,
	AddExcute,

	Delete,
	DeleteExcute,

	Modify,
	ModifyExcute,

	Success,
	Fail,

	QueryAsk,
	QueryAnsNoUpdate,
	QueryAnsUpdate,
	Query,
	QueryExcute,
	QuerySuccess,
	QueryFail,
};

#define STUDENT_ID "studentID"
#define STUDENT_NAME "studentName"
#define STUDENT_SEX "sex"
#define STUDENT_TEL "telephone"
#define COURSE_ID "courseID"
#define COURSE_NAME "courseName"
#define COURSE_GRADE "grade"
#define CLASS_ID "classID"
#define CLASS_NAME "className"

