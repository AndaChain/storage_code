class Time
	def at_beginning_of_year
		return Time.local(Time.now.year,"jan")
	end
end

class Integer
	def day
		return (self * 60 * 60 * 24)
	end
end

puts Time.now.at_beginning_of_year + 1.day

