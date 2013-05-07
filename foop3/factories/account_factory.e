note
	description: "Summary description for {ACCOUNT_FACTORY}."
	author: ""
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
