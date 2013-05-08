note
	description: "this factory produces different accounts"
	date: "$Date$"
	revision: "$Revision$"

class
	ACCOUNT_FACTORY

feature -- factories

	get_studentaccount : ACCOUNT
	local
		student_account : STUDENT_ACCOUNT
		student : STUDENT
	do
		create student.make ("Student")
		create student_account.make (student)
		Result := student_account
	end

	with_owner (owner : PERSON) : ACCOUNT
	require
		owner /= Void
	local
		account : ACCOUNT
	do
		create account.make (owner)
		Result := account
	ensure
		Result /= Void
	end

end
