note
	description: "this factory produces accounts for students"
	date: "$Date$"
	revision: "$Revision$"

class
	ACCOUNT_FACTORY

feature -- factories

	get_account : ACCOUNT
	local
		student_account : STUDENT_ACCOUNT
		student : STUDENT
	do
		create student.make ("Student")
		create student_account.make (student)
		Result := student_account
	end

end
