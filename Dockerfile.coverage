FROM python:3.11-alpine

RUN apk add --update alpine-sdk py3-pip cmake openssl gcc py3-pybind11
RUN python3 -m pip install "pybind11[global]"

COPY . /polygondust

WORKDIR /polygondust