---
title: Specification Phase
authors: Maxime BILLY, Timothée JUILLET, Loïc PANTANO
---

*This part of the work will first require you to determine the system architecture as well as the security
architecture. Your system architecture will have to cope with a major requirement: your boss has
selected a client server communications library from Macrohard Corporation as a middleware for
implementing data transfers, which you must incorporate into your design. Unfortunately, this library
does not implement any security mechanism.*

*Your security architecture will have to describe how security countermeasures are introduced into the
system architecture and how they interact. The security countermeasures will be determined based
on the threat model that you also have to establish. Such countermeasures typically include access
control and cryptography. The threat model will investigate security and privacy threats to the
application and will also have to be documented.*

## 0. Threat Model

Before we can start designing the system architecture and the security architecture, we need to establish a threat model.
The threat model will help us identify the threats to the system and the assets that need to be protected.

### 0.1. Unauthorized access to the system.

Potentially sensitive files could be stored on the server, thus the need to protect them from unauthorized access.

On the server, we will store the files with permissions that will only allow the server to access them.
We will also store the files encrypted at rest, thus even if an attacker manages to access the files, he won't be able to read them.
When transferring the files from the client to the server, we will encrypt the connection between the client and the server, thus even if an attacker manages to intercept the files, he won't be able to read them.

This allows us to protect the files from the moment they leave the client until the moment they are stored on the server.

### 0.2. Remote Code Execution.

The server will be running on a remote machine, thus the need to protect it from remote code execution.

We will reduce the risk of remote code execution by using UNIX bindings and never calling `eval` or `exec` at all.

### 0.3. Data interception

Sensitive data transferred between the client and server may be intercepted by malicious actors during transmission.

We will mitigate this threat by using a secure communication protocols to encrypt data in transit and protect it from interception.

### 0.4. Denial of service

Attackers may flood the server with requests, overwhelming its resources and causing it to become unavailable.

We can prevent this type of attack by monitoring and filtering requests to mitigate the impact of DoS attacks.

## 1. System Architecture

The system architecture is based on a client-server model.
We have noted in the requirements that the client can connect from "Home", that means communication between the client and the server will be done over potentially insecure networks, thus the need to encrypt our communications.

### 1.1. Client

The client will have two major components:

- A CLI (Command Line Interface) that will allow the user to interact with the system.
- The Microhard library that will allow the client to communicate with the server.

### 1.2. Server

The server will have one major components:

- The Microhard library that will allow the server to communicate with the client.

### 1.3. Shared Ressources

Both Server and Clients have access to the wrapped libraries provided by Microhard, they mitigate the risk of buffer overflow and are much more flexible than the provided ones.

### 1.4. Communication

Here is an example of a communication between the client and the server for a file upload:

![Upload](doc/assets/upload.svg)

This is how a download works:

![Download](doc/assets/download.svg)

And this is the way it lists files on the server:

![List](doc/assets/list.svg)

## 2. Security Architecture:

### 2.1 Remote Code Execution (RCE)

To harden our executable from RCEs, we used only the MicroHard and OpenSSL libraries and never called external executables.

We sanitize user input and communications between clients and servers.

### 2.2 Encoding

Using Base64 encoding during file transfer can enhance the safety of your data in several ways. Base64 encoding converts binary data into ASCII characters, making it more resilient to potential issues during transmission, such as character set mismatches or special character handling in different systems. Additionally, Base64 encoding helps prevent data corruption that may occur when transferring binary files through protocols that are not binary-safe.

Moreover, Base64 encoding serves as a form of data obfuscation. Since the encoded data is a string of alphanumeric characters, it reduces the risk of unintended interpretation or manipulation by systems or protocols that may mishandle binary content. This adds a layer of security by making it less likely for malicious entities to tamper with the data during transit.

Furthermore, some file transfer mechanisms or platforms may have restrictions on certain types of binary data. Using Base64 encoding allows you to bypass such limitations, ensuring a smoother and more reliable transfer process. Overall, incorporating Base64 encoding in your file transfer protocol contributes to the integrity and security of your data, minimizing potential risks associated with various transfer environments.

### 2.3 Static Code Analysis

Early in the development stage, we included static code analysis for all of our codebase to detect bad practises, security hotspots and potential vulnerabilities.

It is done with SonarQube and it has allowed us to review some hotspots and asses the risks.

![Sonarqube](doc/assets/sonarqube.png)

*Due to the limited development time, loads of the security measures we planned to implement were not in favor of the main specifications of the application.*

## 3. Security Assessment

### 3.1 Microhard's Library Analysis

We used IDA64 to first reverse engineer the source code behind MicroHard's libraries. This has allowed us two things.

First, this allowed us to crosscompile these libs with arm64 to allow us to develop on new M1 macs, which was impossible with the amd64 compiled libs.

Second, it has allowed us to run SonarQube on the source code, highliting security hotspots and vulnerabilities that were mitigated in the client and server.

### 3.2 Fuzzing

We used a very simple technic to test fuzzing the communications between client and server.

```bash
exec 3<>/dev/tcp/127.0.0.1/8080 # Opens the server's Socket
cat /dev/random >&3 # Sends random bytes in the socket
```

Then we used the fuzzing we've seen during class to test the parsing of our arguments.

```bash
zzuf ./client -up file
zzuf ./client -list
```

These attacks, although very simple, were unable to break our program, wich exited before showing any security weaknesses.

## 4. Conclusion

This program, used with a ssh tunnel, is a secure way of accessing files over the internet.

It is difficult to justify the need for another tool using proprietary libraries from MicroHard when open source, well tested alternatives such as `scp` and `rsync` exist.

Maxime BILLY, Timothée JUILLET, Loïc PANTANO