enum class SelectTable
{
	tb_student,
	tb_course,
	tb_class,
	tb_studentCourse,
	tb_studentClass
};

enum class MessageType
{
	Nop,
	Add,
	AddSuccess,
	AddFail,
	Delete,
	DeleteSuccess,
	DeleteFail,
	Modify,
	ModifySuccess,
	ModifyFail,
	Query,
	QuerySuccess,
	QueryFail,
};