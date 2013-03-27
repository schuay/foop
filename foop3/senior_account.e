note
	description: "Summary description for {PENSION_ACCOUNT}."
	author: ""
	date: "$Date$"
	revision: "$Revision$"

class
	SENIOR_ACCOUNT

inherit
	ACCOUNT
		redefine
			to_string,

			owner,

			min_transaction,

			min_interest,
			max_interest,

			min_overdraft_interest,
			max_overdraft_interest,

			min_balance
		end

create
	make

feature -- Status report

	to_string: STRING

		local
			str: STRING
		do
			str := "SENIOR_ACCOUNT%N"
			Result := str + Precursor
		end

feature -- Access

	owner: SENIOR assign set_owner
		-- The owner of this account.

feature -- Public constants

	min_transaction: DOUBLE once Result := 1.0 end

	min_interest: DOUBLE once Result := 0.0 end
	max_interest: DOUBLE once Result := 0.15 end

	min_overdraft_interest: DOUBLE once Result := 0.00 end
	max_overdraft_interest: DOUBLE once Result := 0.60 end

	min_balance: DOUBLE once Result := -1000.00 end

end
