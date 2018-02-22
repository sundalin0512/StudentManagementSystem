#include "mydefines.h"
const char* strTables[] =
{
	"tb_student",
	"tb_course",
	"tb_class",
	"tb_student_course",
	"tb_student_class",
};

const char* strKeyNames[] =
{
	"studentID",
	"studentName",
	"sex",
	"telephone",
	"courseID",
	"courseName",
	"grade",
	"classID",
	"className",
};
const char* strKeyNamesWithTable[] =
{
	"tb_student.studentID",
	"tb_student.studentName",
	"tb_student.sex",
	"tb_student.telephone",
	"tb_course.courseID",
	"tb_course.courseName",
	"tb_student_course.grade",
	"tb_class.classID",
	"tb_class.className",
};