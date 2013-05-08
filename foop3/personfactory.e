note
	description: "this factory creates a specific person by type and name"
	date: "$Date$"
	revision: "$Revision$"

class
	PERSONFACTORY

feature
	by_type (type : STRING; name : STRING) : PERSON
	require
		type.is_equal ("student") or type.is_equal ("senior")
	local
		student : STUDENT
		senior : SENIOR
	do
		if type.is_equal("student") then
			create student.make (name)
			Result := student
		elseif type.is_equal("senior") then
			create senior.make (name)
			Result := senior
		end
	ensure
		Result /= Void
	end

end
