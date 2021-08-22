=begin
REF http://www.richardshin.com/attr_accessor_with_history/
Note: But we modify the way to keep value in array.
=end
class Module
  def attr_accessor_with_history(attr_name)
    attr_reader attr_name
    attr_reader "#{attr_name}_history"
    class_eval %Q{ #Here make method that can keep previous variable.
      def 
		#{attr_name}=(value)                                  #When set value to setter method value. Do every line below this until "end".
        @#{attr_name}_history = [] if @#{attr_name}_history.nil? #If No any setter method return a empty array.
        @#{attr_name}_history << value                           #"<<" mean push value at the end of the array.
        @#{attr_name} = value                                    #Set value of setter method
      end                                                        #Until this "end"
    }

    class_eval do
      def history(name)
        instance_variable_get("@#{name}_history") # get value of getter method
      end
    end

  end
end

class Foo
  attr_accessor_with_history :bar
end
f = Foo.new     # => #<Foo:0x127e678>
f.bar = 3       # => 3
f.bar = :gg
f.bar = "123"
f.bar = "777"
f.bar = "777"
puts f.history(:bar) # => [3, :wowzo, 'boo!']
