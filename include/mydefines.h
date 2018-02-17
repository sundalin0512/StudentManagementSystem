enum class SelectTable
{
	tb_student,
	tb_course,
	tb_class,
	tb_studentCourse,
	tb_studentClass
};

extern const char* strTables[];

enum class MessageType
{
	Nop,
	NoServer,

	AskSC,
	AnsServer,
	AnsClient,

	Add,
	AddExcute,
	AddSuccess,
	AddFail,
	Delete,
	DeleteExcute,
	DeleteSuccess,
	DeleteFail,
	Modify,
	ModifyExcute,
	ModifySuccess,
	ModifyFail,
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
