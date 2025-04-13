import tkinter as tk
from tkinter import messagebox

# Function to be called when button is clicked
def greet():
    name = entry.get()
    messagebox.showinfo("Greeting", f"Hello, {name}!")

# Create the main window
root = tk.Tk()
root.title("Greeting App")
root.geometry("300x150")

# Add a label
label = tk.Label(root, text="Enter your name:")
label.pack(pady=10)

# Add an entry box
entry = tk.Entry(root)
entry.pack()

# Add a button
button = tk.Button(root, text="Greet Me", command=greet)
button.pack(pady=10)

# Run the application
root.mainloop()
