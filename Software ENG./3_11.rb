class Binarytree
	include Enumerable
	
    def initialize(root)
		@root = root
		@tree = []
    end
    
    def <<(other)
        pushNode(@root, other)
    end
    
    def empty?
		return (@root.value == nil)
	end
    
	def pushNode(node, value)
		if(node.value == nil)
			node = Node.new(value)
			@root = node
		end
		
		if(value > node.value)
			 if(node.right)
			  pushNode(node.right, value)
			 else
			  node.right = Node.new(value)
			 end
		else
			 if(node.left)
			  pushNode(node.left, value)
			 else
			  node.left = Node.new(value)
			 end
		end
	end
	
	def traverse(node)     # by left root right 
		if(node==nil)
			return
		end
		
		if(node.left)
			traverse(node.left)
		end
		@tree << node.value		# for each method left root right
		
		if(node.right)
			traverse(node.right)
		end
		
		#@tree << node.value		# for each method right root left
	end
	
    def each(&block)
		self.traverse(@root)
        @tree.each do |member|
          block.call(member)
        end
    end
end

class Node
    attr_reader :value
    attr_accessor :left, :right
    def initialize(value = nil)
		@value = value
		@left = nil
		@right = nil
    end
end

root = Node.new()
obj = Binarytree.new(root)
obj << 1
obj << 22
obj << 0
obj << -4
obj.each{|s| p s}
